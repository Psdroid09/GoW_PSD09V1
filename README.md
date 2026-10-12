# GoW_PSD09V1 — God of War I para PS Vita

**Versión final estable** del plugin GoW_PSD09, publicada de forma independiente a partir de la **v22** que funcionó en una PS Vita real.

> Compatible exclusivamente con **God of War I**, de **God of War Collection**, **EU v1.00 / PCSF00438**. No se ha verificado en otras regiones, revisiones ni God of War II.

## Características

- Resolución nativa **960 × 544**, sin VitaGrafix ni rePatch.
- **FPS desbloqueados y variables durante la partida**; no obliga al juego a funcionar a 60 FPS.
- **Menú principal, START y SELECT a aproximadamente 30 FPS** (ritmo original) para evitar animaciones aceleradas y parpadeo del texto.
- Cambio entre modos **automático**; no usa combinaciones de botones.
- No intercepta Flash ni cambia el reloj de sus animaciones.
- Solo se ejecuta en el proceso compatible de God of War I.

## Descargar e instalar

El binario **`release/GoW_PSD09.suprx`** se publica automáticamente mediante GitHub Actions; también se puede obtener como artefacto del workflow **Build GoW_PSD09V1**.

1. Necesitas una PS Vita con **HENkaku/taiHEN** y una copia compatible de God of War Collection, región europea **PCSF00438**, versión 1.00.
2. Guarda una copia de tu `ur0:tai/GoW_PSD09.suprx` anterior y de `ur0:tai/config.txt`.
3. Copia el archivo descargado `GoW_PSD09.suprx` a `ur0:tai/`.
4. En `ur0:tai/config.txt`, coloca una sola entrada bajo el identificador del juego:

```ini
*PCSF00438
ur0:tai/GoW_PSD09.suprx
```

5. Evita otros parches simultáneos de FPS o resolución para este juego. Reinicia la Vita y ejecuta God of War I.

El plugin escribe mensajes de instalación y cambios de modo en `ux0:data/GoW_PSD09_v22_MenuSafe.txt`.

## Comportamiento

| Estado | Resolución | FPS |
|---|---|---|
| Partida | 960×544 | Desbloqueados, variables |
| Menú principal | 960×544 | Aproximadamente 30 |
| START | 960×544 | Aproximadamente 30 |
| SELECT | 960×544 | Aproximadamente 30 |

El límite de los menús es deliberado: las versiones experimentales que intentaron animarlos a 60 FPS causaron aceleración o parpadeo. Esta edición conserva el comportamiento de la **v22 comprobada por el usuario**.

## Compilar

Instala [VitaSDK](https://vitasdk.org/) y ejecuta:

```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="$VITASDK/share/vita.toolchain.cmake"
cmake --build build --parallel 2
```

El resultado será `build/GoW_PSD09.suprx`. Alternativamente, el workflow de GitHub Actions compila con `vitasdk/vitasdk:2026.08` y coloca el plugin compilado en `release/` para descarga directa.

## Procedencia y licencia

Código fuente tomado **sin cambios funcionales** de `Psdroid09/GoW1-60FPS-Vita`, rama `experiments/gow-v22-menu-original-fps-20261011`. Este repositorio contiene solamente el plugin y sus fuentes, **no** ejecutables, datos ni recursos de God of War.

No se incluye licencia de código abierto automáticamente; el propietario puede definirla más adelante. La compatibilidad y la estabilidad con plugins de terceros no están garantizadas.
