# GoW_PSDV2 — God of War Collection para PS Vita

Plugin para **God of War Collection** con resolución nativa y ajustes de FPS independientes para ambos juegos.

## Características

- **God of War I:** resolución nativa **960 × 544** y FPS desbloqueados durante la partida. Los menús conservan un límite de aproximadamente **30 FPS** para evitar que sus animaciones se aceleren.
- **God of War II:** resolución nativa **960 × 544** y **30 FPS**, como en el juego original.
- **Sin diagnósticos:** no se generan archivos de registro ni mensajes de depuración, evitando operaciones de escritura innecesarias.
- Configuración para las ediciones **Europa (PCSF00438)** y **USA (PCSA00126)**.

## ¿Por qué God of War II está a 30 FPS?

Al intentar forzar **God of War II a 60 FPS**, se observaron **bajones de rendimiento** y se reportó un **problema en determinadas secuencias que puede impedir avanzar en la historia**.

Por eso se mantiene el límite original de **30 FPS**: se prioriza la estabilidad, se evita alterar el ritmo de las animaciones y se reducen posibles problemas durante las secuencias y eventos del juego. La resolución nativa de **960 × 544** se conserva, así que la mejora de nitidez no depende de desbloquear los FPS.

## Instalación

1. Guarda una copia de `ur0:tai/config.txt` y de tu plugin anterior.
2. Copia `GoW_PSDV2.suprx` en `ur0:tai/`.
3. En `ur0:tai/config.txt`, añade la sección que corresponda a tu juego, **antes de `*ALL` si existe**:

**Europa:**
```ini
*PCSF00438
ur0:tai/GoW_PSDV2.suprx
```

**USA:**
```ini
*PCSA00126
ur0:tai/GoW_PSDV2.suprx
```

4. Usa una sola versión del plugin a la vez. Si tienes **VitaGrafix**, desactiva sus ajustes de **Framebuffer** y **FPS Cap** para God of War Collection, a fin de evitar conflictos.
5. Reinicia la PS Vita y ejecuta el juego.

## Descarga

- Plugin: `GoW_PSDV2.suprx`
- Paquete ZIP: `GoW_PSDV2_GoW2_30FPS_Sin_Logs.zip`
- SHA-256 del plugin: `2b9931a08ddb861bc3b0ac5bb430e533f5a16309403d7159f0fb2ad948aae90b`

**Proyecto:** [Psdroid09](https://github.com/Psdroid09) · **YouTube:** [PsDroid09](https://www.youtube.com/@PsDroid09)
