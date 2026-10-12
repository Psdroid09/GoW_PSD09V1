/* GoW_PSD09 v22: original 30 FPS for menus only, uncapped gameplay.
 * God of War I European 1.00 / PCSF00438 only.
 *
 * v19 solved menu speed by skipping Flash update calls, but made text
 * flicker. v20/v21 executed every Flash call and speedup returned.
 * This version lets the original game run the menu at its stock pacing,
 * including every Flash update and draw, with NO Flash hook at all.
 *
 * NOTE: Deliberate compromise: menus ~30 FPS, gameplay uncapped.
 * The 30fps menu effect must still be verified on actual hardware.
 */
#include <psp2/kernel/modulemgr.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/clib.h>
#include <psp2/io/fcntl.h>
#include <psp2/types.h>
#include <taihen.h>
#include <stdint.h>
#include <string.h>

#define GAME_NAME "Internal3_PSP2_Ship_EUROPE"
#define GAME_NID 0x8638FFEDu
#define GAME_PATH "PCSF00438/GOW1.self"
#define LOG_PATH "ux0:data/GoW_PSD09_v22_MenuSafe.txt"
#define RES_COUNT 9
#define GAME_STATE_OFF 0xADE04u
#define FPS_OFFSET 0x9E228u
#define FPS_ORIGINAL 0x2002u
#define FPS_UNLOCKED 0x2001u

typedef struct { uint32_t offset; uint8_t reg; uint16_t value; } Resolution;
#define W(o,r) {o,r,960}
#define H(o,r) {o,r,544}
static const Resolution resolution[RES_COUNT] = {
 W(0x9E212,4),H(0x9E21A,2),W(0x9F0F0,0),
 H(0x9F0F8,1),W(0xA31C6,7),H(0xA31CC,1),
 W(0xCEF06,0),H(0xCEF0E,2),H(0xA1098,14)
};

static SceUID worker_uid=-1;
static SceUID resolution_uids[RES_COUNT];
static int resolution_count=0;
static SceUID fps_uid=-1;
static SceUID target_modid=-1;
static volatile int running=1;
static volatile int ready=0;
static uintptr_t data_base=0;
static uint32_t data_size=0;

static void log_msg(const char *msg) {
 SceUID fd=sceIoOpen(LOG_PATH,SCE_O_WRONLY|SCE_O_CREAT|SCE_O_APPEND,0666);
 if(fd>=0){sceIoWrite(fd,msg,strlen(msg));sceIoClose(fd);}
}
static void log_hex(const char *label,uint32_t v) {
 char tmp[150];sceClibSnprintf(tmp,sizeof(tmp),"%s%08X\n",label,(unsigned)v);
 log_msg(tmp);
}
static uint32_t read_u32(uintptr_t p) {
 uint32_t r=0;memcpy(&r,(const void*)p,sizeof(r));return r;
}
static int matches_original(uintptr_t p,uint8_t r,uint16_t v) {
 uint16_t lo=0,hi=0;
 memcpy(&lo,(const void*)p,2);
 memcpy(&hi,(const void*)(p+2u),2);
 const uint16_t expected=(uint16_t)(0x7000u|((uint16_t)r<<8)|(v==960?0x34u:0xCCu));
 return lo==0xF45Fu && hi==expected;
}
static void make_resolution(uint8_t r,uint16_t v,uint8_t out[4]) {
 const uint16_t lo=0xF45Fu;
 const uint16_t hi=(uint16_t)(0x7000u|((uint16_t)r<<8)|(v==960?0x70u:0x08u));
 memcpy(out,&lo,2);memcpy(out+2,&hi,2);
}
/* If patched, this restores the original two-vblank instruction.
 * No state-dependent input shortcuts and no Flash calls are skipped. */
static int set_fps_unlock(int unlock) {
 if(target_modid<0)return -1;
 if(unlock) {
  if(fps_uid>=0)return 0;
  const uint16_t instruction=FPS_UNLOCKED;
  SceUID uid=taiInjectData(target_modid,0,FPS_OFFSET,&instruction,2);
  if(uid<0){log_hex("WARN FPS unlock injection failed: 0x",(uint32_t)uid);return -1;}
  fps_uid=uid;
  return 0;
 }
 if(fps_uid<0)return 0;
 SceUID old=fps_uid;
 int ret=taiInjectRelease(old);
 if(ret<0){log_hex("WARN FPS cap restore failed: 0x",(uint32_t)ret);return -1;}
 fps_uid=-1;
 return 0;
}
static void rollback(void) {
 ready=0;
 if(fps_uid>=0) {
  taiInjectRelease(fps_uid);fps_uid=-1;
 }
 for(int i=resolution_count-1;i>=0;i--)taiInjectRelease(resolution_uids[i]);
 resolution_count=0;
 target_modid=-1;data_base=0;data_size=0;
}
static int install(const tai_module_info_t *mod) {
 SceKernelModuleInfo info;memset(&info,0,sizeof(info));info.size=sizeof(info);
 int ret=sceKernelGetModuleInfo(mod->modid,&info);
 if(ret<0){log_hex("FAIL sceKernelGetModuleInfo 0x",(uint32_t)ret);return -1;}
 info.path[sizeof(info.path)-1]=0;
 if(!strstr(info.path,GAME_PATH)) {
  log_msg("FAIL wrong GOW1 executable; no changes.\n");return -1;
 }
 const uintptr_t base=(uintptr_t)info.segments[0].vaddr;
 const uint32_t text_size=info.segments[0].memsz;
 const uintptr_t db=(uintptr_t)info.segments[1].vaddr;
 const uint32_t ds=info.segments[1].memsz;
 if(!base||!db||text_size<0xCEF12u||ds<GAME_STATE_OFF+4u){
  log_msg("FAIL module segment bounds; no changes.\n");return -1;
 }
 for(int i=0;i<RES_COUNT;i++) {
  uint32_t off=resolution[i].offset;
  if(off>text_size||text_size-off<4u ||
     !matches_original(base+off,resolution[i].reg,resolution[i].value)){
   log_hex("FAIL resolution opcode offset 0x",off);return -1;
  }
 }
 uint16_t old=0;
 memcpy(&old,(const void*)(base+FPS_OFFSET),2);
 if(old!=FPS_ORIGINAL){
  log_hex("FAIL unexpected FPS opcode 0x",(uint32_t)old);return -1;
 }
 target_modid=mod->modid;
 data_base=db;data_size=ds;
 for(int i=0;i<RES_COUNT;i++) {
  uint8_t payload[4];make_resolution(resolution[i].reg,resolution[i].value,payload);
  SceUID uid=taiInjectData(target_modid,0,resolution[i].offset,payload,4);
  if(uid<0){
   log_hex("FAIL resolution patch 0x",(uint32_t)uid);
   rollback();return -1;
  }
  resolution_uids[resolution_count++]=uid;
 }
 /* Menus must run at original speed. Start from original opcode.
  * Worker monitors game state and unlocks gameplay automatically. */
 ready=1;
 log_msg("OK native resolution 960x544; no Flash hook or skipped draws.\n");
 log_msg("FPS mode: original 30 for menu; unlock for gameplay.\n");
 return 0;
}
static int is_menu(uint32_t state) {
 return state==3u||state==4u||state==12u||state==13u;
}
static int worker(SceSize argc,void *argv) {
 (void)argc;(void)argv;
 tai_module_info_t mod;int located=0;
 for(int i=0;running && i<600;i++) {
  memset(&mod,0,sizeof(mod));mod.size=sizeof(mod);
  if(taiGetModuleInfo(GAME_NAME,&mod)>=0) {
   located=1;break;
  }
  sceKernelDelayThread(100000);
 }
 if(!running)return 0;
 if(!located){
  log_msg("WARN module not found within 60 seconds.\n");return 0;
 }
 if(mod.module_nid!=GAME_NID){
  log_hex("FAIL module NID mismatch 0x",mod.module_nid);return 0;
 }
 if(install(&mod)<0)return 0;
 int mode=-1,had_error=0;
 while(running && ready) {
  uint32_t state=read_u32(data_base+GAME_STATE_OFF);
  int menu=is_menu(state);
  int want_unlock=!menu;
  if(mode!=want_unlock) {
   if(set_fps_unlock(want_unlock)==0) {
    mode=want_unlock;
    char msg[128];
    sceClibSnprintf(msg,sizeof(msg),
      "MODE state=%u mode=%s\n",(unsigned)state,
      mode?"GAMEPLAY_UNCAPPED":"MENU_ORIGINAL_30");
    log_msg(msg);
    had_error=0;
   } else if(!had_error) {
    log_msg("WARN mode switch failed; original 30 FPS fallback retained.\n");
    had_error=1;
   }
  }
  sceKernelDelayThread(10000);
 }
 return 0;
}
int module_start(SceSize argc,const void *args) {
 (void)argc;(void)args;running=1;
 log_msg("GoW_PSD09 v22 menu-original-30 / gameplay-unlocked (EU 1.00)\n");
 worker_uid=sceKernelCreateThread("gow_v22_menu",worker,0x10000100,0x5000,0,0,NULL);
 if(worker_uid>=0)sceKernelStartThread(worker_uid,0,NULL);
 else log_msg("FAIL worker creation.\n");
 return SCE_KERNEL_START_SUCCESS;
}
int module_stop(SceSize argc,const void *args) {
 (void)argc;(void)args;running=0;
 if(worker_uid>=0){
  sceKernelWaitThreadEnd(worker_uid,NULL,NULL);
  sceKernelDeleteThread(worker_uid);worker_uid=-1;
 }
 rollback();
 return SCE_KERNEL_STOP_SUCCESS;
}
