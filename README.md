# GoW_PSD09V1 — God of War I para PS Vita — Sin diagnóstico

**Versión sin diagnóstico** del plugin GoW_PSD09 V1, basada en la **v22**, probada en una PS Vita real. Esta edición elimina los registros y las funciones auxiliares relacionadas con ellos, pero conserva los parches y el control automático de FPS de la V1. Se compiló y se revisó su estructura, aunque esta nueva versión todavía necesita pruebas en una PS Vita real.

> Compatible exclusivamente con **God of War I**, de **God of War Collection**, **EU v1.00 / PCSF00438**. No se ha verificado en otras regiones, revisiones ni God of War II.


<p align="center">
  <img src="assets/aviso-ia.svg" width="100%" alt="ESTE PLUGIN FUE REALIZADO CON AYUDA DE LA IA, ASI QUE NO LEO LLOROS">
</p>

## Características

- Resolución nativa **960 × 544**, sin VitaGrafix ni rePatch.
- **FPS desbloqueados y variables durante la partida**; no obliga al juego a funcionar a 60 FPS.
- **Menú principal, START y SELECT a aproximadamente 30 FPS** (ritmo original) para evitar animaciones aceleradas y parpadeo del texto.
- Cambio entre modos **automático**; no usa combinaciones de botones.
- No intercepta Flash ni cambia el reloj de sus animaciones.
- Solo se ejecuta en el proceso compatible de God of War I.
- **Sin diagnósticos, registros, telemetría ni volcados de memoria.** No crea ni escribe archivos de diagnóstico.

## Descargar e instalar

**[Descargar la versión «GoW_PSD09 V1 — Sin diagnóstico»](https://github.com/Psdroid09/GoW_PSD09V1/releases/tag/v1-sin-diagnostico)**. La versión anterior continúa disponible por separado.

1. Necesitas una PS Vita con **HENkaku/taiHEN** y una copia compatible de God of War Collection, región europea **PCSF00438**, versión 1.00.
2. Guarda una copia de tu `ur0:tai/config.txt`.
3. Copia el archivo descargado `GoW_PSD09.suprx` a `ur0:tai/`.
4. En `ur0:tai/config.txt`, coloca una sola entrada bajo el identificador del juego:

```ini
*PCSF00438
ur0:tai/GoW_PSD09.suprx
```

5. Evita otros parches simultáneos de FPS o resolución para este juego. Reinicia la Vita y ejecuta God of War I.

Esta edición **no genera diagnósticos ni registra cambios de modo**. Si quedó un archivo `ux0:data/GoW_PSD09_v22_MenuSafe.txt` de una versión anterior, puedes borrarlo manualmente; esta edición no lo crea, modifica ni elimina.

Conserva las comprobaciones de compatibilidad necesarias antes de aplicar los parches y la lectura del estado del juego para cambiar automáticamente entre menú y partida.

## Comportamiento

| Estado | Resolución | FPS |
|---|---|---|
| Partida | 960×544 | Desbloqueados, variables |
| Menú principal | 960×544 | Aproximadamente 30 |
| START | 960×544 | Aproximadamente 30 |
| SELECT | 960×544 | Aproximadamente 30 |

El límite de los menús es intencional: las versiones experimentales que intentaron mostrar sus animaciones a 60 FPS provocaron aceleración o parpadeos. Esta edición conserva el comportamiento de la **v22, probado en una PS Vita real**.

## Reportes de errores y comentarios

¿Encontraste algún problema con el plugin o tienes una sugerencia?

- 💬 **[Dejar un comentario o consultar un error](https://github.com/Psdroid09/GoW_PSD09V1/issues/1)**: hilo abierto para compartir experiencias, dudas, capturas y videos.
- 🐞 **[Reportar un error por separado](https://github.com/Psdroid09/GoW_PSD09V1/issues/new?template=bug_report.yml)**: formulario para describir un fallo y darle seguimiento.

Incluye, si puedes, la versión del plugin, la región del juego, cómo ocurrió el error y los plugins relacionados. **Esta edición no genera diagnósticos.** Para ayudar a identificar los errores, puedes **probar la versión anterior, que incluye diagnósticos**, y compartir los resultados.

## Mi canal de YouTube

📺 **¡Apoya este proyecto!** Si te gustó el plugin, te invito a visitar y suscribirte a mi canal de YouTube: **[PsDroid09](https://www.youtube.com/@PsDroid09)**.

## Contribución

**Único autor del proyecto: [Psdroid09](https://github.com/Psdroid09).**

Este repositorio público distribuye solamente el plugin compilado; **el código fuente no se incluye**. No contiene archivos, datos ni recursos de God of War.
