## Plugin sin diagnóstico

Edición de **GoW_PSD09 V1 sin diagnósticos ni registros**.

- Eliminadas las rutinas de registro, el formateo de mensajes y la escritura del archivo de diagnóstico.
- No crea archivos de diagnóstico, telemetría ni volcados de memoria.
- Conserva la resolución **960 × 544**, los **FPS desbloqueados durante la partida** y los **menús, START y SELECT a aproximadamente 30 FPS**.
- Mantiene el cambio automático de FPS y las comprobaciones necesarias de compatibilidad.

**Compatible exclusivamente con God of War I EU v1.00 (PCSF00438).**

Reemplaza `ur0:tai/GoW_PSD09.suprx` por el archivo adjunto y reinicia la Vita. No necesitas cambiar la entrada existente del plugin en `config.txt`. Evita otros parches simultáneos de FPS o resolución para este juego.

La publicación anterior permanece disponible. Los archivos de diagnóstico antiguos no se borran automáticamente.

**Validación:** compilación con VitaSDK y revisión estática del ejecutable para comprobar la ausencia de rutinas e importaciones de registro y escritura de archivos. Esta nueva compilación aún no se ha probado en una PS Vita real.
