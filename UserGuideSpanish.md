|<font color='red'><b>WARNING</b>: This guide is at least one major version behind the latest official release, and thus may contain inaccuracies or outdated information.</font>|
|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|

# Translation #

Spanish translation provided by Jmtd.
Traducción al español realizada por Jmtd.

# Tabla de Contenidos #

  * [Tabla de Contenidos](UserGuideSpanish#Tabla_de_Contenidos.md)
  * [Introduccion](UserGuideSpanish#Introduccion.md)
  * [El menu de ajustes](UserGuideSpanish#El_menu_de_ajustes.md)
  * [Los Guiones](UserGuideSpanish#Los_Guiones.md)
  * [Los preajustes (presets)](UserGuideSpanish#Los_preajustes_(presets).md)
  * [AutoISO](UserGuideSpanish#AutoISO.md)
  * [ISO en visor](UserGuideSpanish#ISO_en_visor.md)
  * [Seleccion del Patron AF](UserGuideSpanish#Seleccion_del_patron_AF.md)
  * [Los extras](UserGuideSpanish#Los_extras.md)
  * [Otros regalos](UserGuideSpanish#Otros_regalos.md)
  * [Notas](UserGuideSpanish#Notas.md)
  * [Errores conocidos](UserGuideSpanish#Errores_conocidos.md)

# Introduccion #

## Qué es 400plus? ##

**400plus** es un software libre de mejora del firmware que ofrece funcionalidades adicionales para tu cámara Canon 400D/XTi de manera tanto no destructiva como no permanente. Funciona cargándose automáticamente en la memoria de tu cámara en el arranque para mejorar el firmware original de la cámara, pero no es una actualización permanente del firmware y se puede quitar fácilmente. Está diseñado específicamente para la Canon EOS 400D/XTi y no funciona con otros modelos de cámara.

## Guía del Usuario ##

Este documento hará las funciones de guía de usuario para 400plus. Se supone que, antes de leer esta guía, el usuario ha instalado 400plus y funciona correctamente. Para más información acerca de la instalación de 400plus, ver [FirmwareHackInstallation](http://code.google.com/p/400plus/wiki/FirmwareHackInstallation).

# El menu de ajustes #

## Acceso al menú de ajustes ##

Para entrar en el menú 400plus, pulsa el botón de IMPRESIÓN DIRECTA desde el menú principal de la cámara. Para salir del menú 400plus presiona hasta la mitad el botón disparador. NOTA: el botón de IMPRESIÓN DIRECTA se encuentra en la parte posterior de la cámara a la izquierda del visor (al lado del icono de la impresora de color azul con la línea de la flecha ondulada).

## Navegación por el menú de ajustes ##

400plus presenta ahora un menú de varias páginas, donde cada página está dedicada a una tarea determinada. Para navegar a través de las páginas, utiliza la rueda delantera o los botones ZOOM + / ZOOM - (fíjate que aparecen los signos  <<   y   >>  en la cabecera). También existe un método para acceder rápidamente a cualquier página: presiona y mantén presionado el botón AV y aparecerá una lista de todas las páginas disponibles; a continuación, utiliza el dial frontal para seleccionar una página, y suelta el botón AV para saltar a ella.

Para navegar dentro de una página, utiliza los botones ARRIBA (ISO) y ABAJO (WB); a continuación, utiliza los botones IZQUIERDA (MODO DE MEDICIÓN) y DERECHA (AF) para cambiar el valor del elemento seleccionado (presiona y mantén presionado estos botones para cambiar más rápido). Los elementos que presentan a la izquierda un signo de exclamación " ! " realizan una acción; puedes activarlos con el botón SET. Y los elementos con un signo " > " a la derecha son los sub-menús; puedes entrar en ellos con el botón DERECHA, y volver a la página principal con el botón AV. Ten en cuenta que algunos ítems pueden tanto realizar una acción como tener un sub-menú.

## Configuración del menú ##

Estando en cualquier página del menú, tienes la posibilidad de cambiar el orden de los elementos según tu propia preferencia personal. Para ello, basta con pulsar el botón PLAY para "agarrar" un elemento (un pequeño ">" aparecerá a la izquierda del ítem). Ahora usa los botones ARRIBA o ABAJO para colocar el elemento del menú en el lugar que te gustaría que ocupara (verás que el ítem se ha movido a la nueva posición). Finaliza el proceso pulsando de nuevo el botón PLAY para guardar los cambios.

## Páginas ##

### Parámetros ###

  * _**AutoISO**_: Este sub-menú configura el comportamiento de [AutoISO](UserGuideSpanish#AutoISO.md).
    * Activo: cuando está puesto en "Sí", el AutoISO está activo.
    * Mín ISO: mínimo valor ISO que AutoISO usará.
    * Máx ISO: máximo valor ISO que AutoISO usará.
    * Mín Tv: mínima velocidad de obturación que AutoISO tratará de mantener.
    * Máx Av: máxima apertura de diafragma que AutoISO tratará de mantener `[*]`.
  * _**ISO**_: Cambia los ISOs intermedios. Los valores oscilan entre 100 y 3000.
  * _**Comp. Av**_: Igual que la función "compensación AV", pero extiende su rango de -6 a +6 EV.
  * **_AEB_**: Igual que la función "AEB", pero extiende el rango desde -6 a +6 EV.
  * _**Temp. color (K)**_: Establece una temperatura de color definida por el usuario y cambia el balance de blancos WB a 'personalizado'.
  * _**Bloqueo espejo**_: activa / desactiva la función personalizable de bloqueo de espejo. (similar a la función persanalizada C.Fn 07).
  * _**Desplazam. seg.**_: Desplazamiento de Seguridad. Cuando está activo (puesto en "Sí"), y si estamos en los modos Tv (o Av), la cámara cambiará la velocidad de obturación (o la apertura del diafragma) fijados por el usuario para evitar una sub/sobre-exposición, si el valor es demasiado pequeño/grande para la escena.
  * _**Flash**_: Ajustes del Flash.
    * Comp. flash: Igual que la función "compensación del flash", pero puede ir de -6 a +6 EV.
    * Bloquea Flash: Fuerza la desactivación del flash durante el disparo actual, aunque se haya elevado el flash.
    * Flash AF: Activa o desactiva el flash (durante la fase de AF), aunque se haya elevado. Los valores son "activo", "inactivo" o "sólo ext" (similar a la función persanalizada C.Fn 05).
    * Flash 2ª cortinilla: Activa / desactiva la sincronización del flash a la función personalizable de cortinilla trasera. (similar a la función persanalizada C.Fn 09).
  * _**IR Remoto**_: Ajustes del control remoto por infrarrojos.
    * IR Activo: Cuando está en "Sí" permite el uso del control remoto por infrarrojos. Si se fija en "No" se desactiva.
    * Retardo IR: Selecciona si la cámara debe tomar la foto inmediatamente o esperar 2 segundos cuando se usa el control remoto por infrarrojos.

`[*]` _Ten en cuenta que el rango de valores que admite este parámetro está limitado por las capacidades físicas de tu lente; en una lente zoom, la apertura máxima del objetivo puede ser diferente para cada posición del zoom. Por favor, ten este hecho en cuenta al establecer este valor._



### Página de Guiones ###

  * _**AEB extendido**_: Este ítem lanza y configura el guión del [AEB Extendido](UserGuideSpanish#AEB_Extendido.md).
    * Demora 2s: selecciona si el guión empieza a disparar inmediatamente o debe esperar 2 segundos.
    * Marcos: número de tomas a disparar. Los valores van de 1 a 9.
    * Paso (EV): separación en EV (valor de exposición) entre cada marco (disparo). Los valores van desde +1/3EV hasta +6EV.
    * Dirección: especifica la dirección de la secuencia EAEB.
    * Bulb min: velocidad mínima del obturador en modo BULB (puede ir desde 1/4000 de segundo hasta 32 minutos).
    * Bulb máx: velocidad máxima del obturador en modo BULB (puede ir desde 1/4000 de segundo hasta 32 minutos).
  * _**Flash AEB**_: Este sub-menú lanza y configura el guión del [Flash AEB](UserGuideSpanish#Flash_AEB.md).
  * _**ISO AEB**_: Este ítem lanza y configura el guión del [ISO AEB](UserGuideSpanish#ISO_AEB.md); cada elemento en el submenú de configuración indica si la cámara debe disparar una toma para ese valor ISO.
  * _**Intervalómetro**_: Este ítem lanza y configura la secuencia de comandos [Intervalómetro](UserGuideSpanish#Intervalometro.md).
    * Demora 2s: selecciona si el guión debe empezar a disparar inmediatamente o esperar 2 segundos.
    * Acción: la acción a realizar (una toma, AEB extendido, Flash AEB, ISO AEB, Larga Exposición).
    * Tiempo: el intervalo de tiempo (en minutos:segundos) entre cada disparo (o grupo de disparos). Los valores van desde 00:01 hasta 05:00.
    * Tomas: el número total de disparos a hacer. Los valores van desde 1 a 250, e incluye también el valor "sin límite" para disparar sin cesar.
    * Formato video (fps): velocidad de fotogramas prevista, al preparar un time-lapse.
    * Tiempo grabación: el tiempo estimado que la cámara necesitará para grabar la totalidad del time-lapse (sólo informativo).
    * Tiempo reproducción: el tiempo de reproducción estimado del time-lapse resultante (sólo informativo).
  * _**Toma X Visor**_: Este ítem lanza y configura el guión de la [Toma por Visor (ondeo)](UserGuideSpanish#Toma_por_Visor_(ondeo).md).
    * Demora: selecciona el disparo inmediato, o una demora de 2 segundos.
    * Acción: la acción a realizar (una toma, AEB extendido, Flash AEB, ISO AEB, Larga Exposición).
    * Repetición: si se selecciona (puesto en "Sí"), el guión se reiniciará después de haberse completado, por lo que puedes mover la mano de nuevo para continuar usando el guión.
    * Instantánea: si se selecciona (puesto en "Sí"), se produce la toma tan pronto como se detecta una mano; de lo contrario, el guión va a esperar hasta que la mano se retira.
  * _**Temporizador**_: Este sub-menú lanza y configura la secuencia de comandos del [Temporizador](UserGuideSpanish#Temporizador.md).
    * Tiempo: tiempo (en minutos:segundos) que el guión debe esperar antes de disparar. Los valores van desde 00:00 hasta 05:00.
    * Acción: la acción a realizar (una toma, AEB extendido, Flash AEB, ISO AEB, Larga Exposición).
  * _**Larga Exposición**_: Este sub-menú lanza y configura la secuencia de comandos [Larga Exposición](UserGuideSpanish#Larga_Exposicion.md).
    * Demora 2s: selecciona el disparo inmediato, o una demora de 2 segundos.
    * Tiempo: la duración (en minutos:segundos) de la exposición. Los valores van desde 00:15 hasta 100:00.
    * Calculador: entra en el [Calculador Larga Exposición](UserGuideSpanish#Calculador_Larga_Exposicion.md).
  * _**Calculadora DOF**_: Este ítem lanza el [Calculadora DOF](UserGuideSpanish#Calculadora_DOF.md).
    * Long. Focal (mm): longitud focal de la lente, en milímetros.
    * Av: apertura de la lente.
    * Distancia Focal (m): distancia focal.
    * Mín. DOF (m): distancia próxima de nitidez aceptable (sólo informativo).
    * Máx. DOF (m): distancia de fondo de nitidez aceptable (sólo informativo).


### Página de Información ###

  * _**Disparos totales**_: El número total de disparos hechos por la cámara.
  * _**ID del cuerpo**_: El número del cuerpo de la cámara (un número interno, único de cada cámara).
  * _**Versión**_: El número de la versión del software 400plus actualmente instalado.


### Pagina de Ajustes ###

  * _**Idioma**_: Ajusta el idioma de los menús de la 400plus; dejar como "Camera", para usar el mismo idioma configurado en los menús de la cámara, o bien situar directamente en SPANISH.
  * _**ISO en visor**_: Cuando se activa (puesto en "Sí"), utiliza los botones del pad para mostrar y cambiar el ISO mientras miras por el visor. Véase [ISO en visor](UserGuideSpanish#ISO_en_visor.md) para más información.
  * _**Menú de desarrolladores**_: Cuando se activa (puesto en "Sí"), el menú será accesible como una página.
  * _**Config. guiones**_: Este sub-menú configura el comportamiento de [Los Guiones](UserGuideSpanish#Los_Guiones.md).
    * Desactivar apagado: cuando está activo (puesto en "Sí"), la opción de auto-apagado de la cámara está desactivada. El valor se restaura después de que el guión se haya completado.
    * LCD: configura el brillo de la pantalla LCD mientras el guíón se ejecuta.
    * Indicador: configura la frecuencia de parpadeo del LED azul, mientras el guión se ejecuta.
  * _**Config. botones**_: En este sub-menú, el usuario puede configurar el comportamiento de algunos botones especiales.
    * Botón DISP: Cuando se activa (puesto en "Sí"), el botón DISP cambiará el brillo de la pantalla en pequeños incrementos, en vez de simplemente encender/apagar.
    * JUMP: Asigna una acción al botón JUMP desde el menú principal de la cámara.
      * ISO intermedio: cambia ISO 1/8EV (ver [Notas/ISOs Extendidos](UserGuideSpanish#ISOs_Extendidos.md)).
      * Repetir guión: repite el último guión ejecutado.
      * Bloqueo espejo: conmuta entre bloqueo de espejo encendido/apagado.
      * AEB: modifica la separación AEB desde 0EV a 1EV, 2EV, y de nuevo a 0EV (apagado).
    * Papelera: igual que el botón JUMP.
  * _**Config. presets**_: Este menú configura el comportamiento de [Los Preajustes](UserGuideSpanish#Los_preajustes_(presets).md).
    * Usa A-DEP: cuando está activo (puesto en "Sí"), el modo A-DEP es "secuestrado" por [Los Preajustes](UserGuideSpanish#Los_preajustes_(presets).md). Lee [El modo A-DEP](UserGuideSpanish#El_modo_A-DEP.md) para más información.
    * Cámara: cuando está activo (puesto en "Sí"), la carga de un preset reclama los parámetros de disparo de la cámara (velocidad de obturación, apertura, ISO,...).
    * 400plus: cuando está activo (puesto en "Sí"), la carga de un preset reclama los propios ajustes 400plus (guiones,...).
    * Ajustes: cuando está activo (puesto en "Sí"), la carga de un preset reclama los ajustes rara vez cambiados (lenguaje, sistema de video,...).
    * Imagen: cuando está activo (puesto en "Sí"), la carga de un preset reclama los parámetros relativos a la imagen (RAW/JPEG, calidad,...).
    * Funciones personalizables: cuando está activo (puesto en "Sí"), la carga de un preset reclama las funciones personalizables C.Fn (bloqueo de espejo, reducción de ruido a larga exposición,...).
  * _**Config. páginas**_: Utiliza este sub-menú para configurar el orden en que se deben mostrar las páginas.

### Página de Presets ###

Utiliza esta página para cargar, guardar y renombrar [Los Preajustes](UserGuideSpanish#Los_preajustes_(presets).md). El procedimiento para renombrar un preset es:

  * Selecciona la opción "Renombra" en el sub-menú presets.
  * Utiliza ARRIBA / ABAJO / IZQUIERDA / DERECHA para seleccionar un valor.
  * Utiliza el botón MENU para alternar entre minúsculas/números y mayúsculas/símbolos.
  * Utiliza el botón JUMP para cambiar el tipo de letra del valor seleccionado en el nombre (línea inferior).
  * Utiliza el botón SET para usar el valor seleccionado en el nombre y avanzar el cursor a la siguiente posición.
  * Utiliza el dial frontal o los botones de ZOOM + /ZOOM - para mover el cursor en la línea de nombre del preset (línea inferior).
  * Presiona el botón AV para guardar tus cambios y volver al menú anterior.

Fíjate que siempre hay un número que aparece a la izquierda de cada preset. Esta característica es útil cuando quieras copiar presets a y desde varias tarjetas CF y necesitas saber los nombres de archivo para cada uno de tus presets: el número a la izquierda de un elemento coincide con el número del archivo creado en la tarjeta CF.

### Página Desarrolladores ###

**NOTA**: La página de los desarrolladores está desactivada por defecto, y debe estar habilitada en la [Página de Ajustes](UserGuideSpanish#Pagina_de_Ajustes.md) antes de acceder a ella. Además, la página de desarrolladores queda fuera de la navegación normal de la página: presiona el botón de la Papelera, estando en el menú, para entrar en la página de los desarrolladores.

_Esta página se ha dejado deliberadamente en blanco._

**ADVERTENCIA**: Las opciones contenidas en esta página deben usarse con sumo cuidado; probablemente hay poco que ver aquí, a no ser que quieras desarrollar tu propio hack.


# Los Guiones #

Cuando una secuencia de comandos se inicia o se detiene, se oirá un beep y, al tiempo que el guión se ejecuta, el botón de IMPRESIÓN DIRECTA parpadea (dos veces por segundo, aproximadamente). Para detener una secuencia de comandos en ejecución, presiona el botón de IMPRESIÓN DIRECTA de nuevo; a veces la cámara no puede parar de inmediato, entonces presiona y mantén presionado el botón de IMPRESIÓN DIRECTA hasta que oigas el beep que indica el final efectivo del guión.

Todas las secuencias de comandos comprobarán la capacidad de la tarjeta antes de cada disparo; si el número estimado de disparos disponibles es inferior a un valor fijo (3), los guiones dejarán de ejecutarse.

## AEB Extendido ##

Esta secuencia de comandos realiza la misma tarea que la opción AEB estándar de la cámara, pero con algunas diferencias interesantes:

  * Se pueden especificar hasta 9 tomas.
  * La separación entre las tomas se puede configurar hasta +-6EV.
  * La cámara tomará todas las fotos en una secuencia, de forma automática.
  * El usuario puede especificar la _dirección_ de la secuencia.

Suponiendo una configuración de 5 disparos con una separación de 1EV, así es como cada dirección se supone que funciona:

  * +/-: Una foto al EV actual, y el resto por encima y por debajo de él: 0EV, +1EV, -1EV, +2EV,-2EV.
  * +: Una foto al EV actual, y el resto por encima de él: 0EV, +1EV, +2EV, +3EV, +4EV.
  * -: Una foto al EV actual, y el resto por debajo de él: 0EV, -1EV, -2EV, -3EV, -4EV.

En el modo 'M' con el valor de apertura fijado en BULB, este guión disparará la cámara tantas veces como sea necesario (en este modo, el número de disparos configurado es irrelevante), con velocidades de obturación que van desde el valor "Bulb mín:" hasta el valor "Bulb máx:", separando cada disparo de acuerdo con el valor del "Paso (EV)". Recuerda que en este modo podemos usar tiempos de exposición de hasta 32 minutos.

## Flash AEB ##

Igual que en el guión del [AEB Extendido](UserGuideSpanish#AEB_Extendido.md), pero sólo la compensación de la exposición del flash va a cambiar.

## ISO AEB ##

La cámara hace una fotografía para cada ISO configurado.

Probablemente desees configurar la cámara en el modo M antes de usar este guión.

## Intervalometro ##

Este guión disparará la cámara tantas veces como se haya configurado (o sin fin), con una demora configurable entre disparos. Úsalo, por ejemplo, para crear películas de _stop-motion_.

### Programación Estricta ###

Ten en cuenta que 400plus siempre tratará de mantener una cadencia constante de disparos, independientemente del tiempo de exposición: si está configurada para disparar, por ejemplo, a intervalos de 15s, entonces hará una fotografía exactamente cada 15 segundos, incluso si la exposición es de 10s. Si un disparo en la secuencia tiene un tiempo de exposición más largo que el intervalo de tiempo configurado, 400plus se saltará tantos disparos como sea necesario y reprogramará la secuencia. Esto también ocurrirá cuando el intervalómetro esté configurado para disparar cualquier acción multi-disparo.

Por ejemplo, imagina un intervalo de 5 segundos, y exposiciones que oscilan entre 1 y 4 segundos (supongamos que la cámara está en el modo Av, y las condiciones de iluminación cambian durante la secuencia de comandos):

```
Time (s) : # · · · · # · · · · # · · · · # · · · ·
Exposure : * *       * * * *   *         * *
```

Observa cómo la longitud de la pausa entre el final de una exposición y el comienzo de la siguiente se adapta al tiempo de exposición, por lo que las fotografías siempre comienzan a intervalos regulares. Ahora imagina que una de las exposiciones tarda más de 5 segundos (digamos 7):

```
Time (s) : # · · · · # · · · · # · · · · # · · · ·
Exposure : * *       * * * * * * *       * *
```

Fíjate que la tercera toma no tiene lugar 5 segundos después de la segunda, sino al segundo 15.

**NOTA**: '400plus' no validará que los valores introducidos por el usuario tengan sentido en absoluto: no se 'quejará' si, por ejemplo, estableces un intervalo de tiempo de 10 segundos y un tiempo de exposición de 15; es el usuario el único responsable de evitar estas situaciones.

### Calculador de Time-lapse ###

Si pretendes hacer una película de time-lapse con las fotografías tomadas con esta secuencia de comandos, puedes especificar la velocidad de fotogramas deseada, y el guión calculará el tiempo de reproducción resultante. Estos parámetros son meramente informativos y no tienen ninguna influencia en el guión.

## Toma por Visor (ondeo) ##

Este guión disparará la cámara cuando el "sensor de apagado de la pantalla" (en la parte posterior de la cámara) se active. Úsalo para disparar la cámara sin la necesidad de un control remoto y evitar así trepidaciones. Si la opción "Repetición" está activada, el guión no terminará después de ser disparado, sino que se repetirá de nuevo para que puedas realizar más tomas. De forma predeterminada, el guión esperará hasta que algo (como tu mano o tu dedo) bloquee el sensor y luego se retire para disparar la cámara. Sin embargo, cuando esté activada la opción " Instantánea", se disparará la cámara tan pronto como se bloquee el sensor.

## Temporizador ##

Este guión simplemente añade una pausa configurable antes de disparar la cámara.

## Larga Exposicion ##

Exactamente eso, una larga exposición configurable desde 15 segundos hasta 100 minutos.

Ten en cuenta que la cámara tiene que estar en el modo M + BULB para hacer una exposición larga; este guión ajustará la cámara por tí, pero la configuración de la abertura adecuada es responsabilidad del usuario.

## Calculador Larga Exposicion ##

El calculador de larga exposición es una herramienta creada para ayudar al fotógrafo a determinar rápidamente el tiempo de exposición requerido por una escena en particular. La idea que hay detrás del calculador es que puedas medir rápidamente una escena usando una alta sensibilidad ISO y una gran apertura, para luego bajar el valor ISO y reducir la abertura, pero aumentando el tiempo de exposición en consecuencia.

Por ejemplo, supongamos que queremos fotografiar una escena nocturna; decidimos utilizar la sensibilidad más baja posible (100 ISO) para evitar el ruido, y una apertura relativamente cerrada (f/8), para obtener la profundidad de campo que necesitamos. Utilizando estos parámetros, el tiempo de exposición necesario puede fácilmente sobrepasar los 30 segundos, y por ello no podemos usar la cámara para hacer una medición fiable.

Pero podemos seleccionar temporalmente una alta sensibilidad y una gran apertura (por ejemplo ISO1600 y f/2.8), medir la escena, y determinar que necesitaríamos una exposición de 15 segundos con esos parámetros. Luego entramos en el calculador de larga exposición, reducimos el valor ISO a 100, y cerramos el diafragma a f/8; el indicador de EV mostrará un valor de -9, lo que significa que con los parámetros actuales la exposición es 9 pasos inferior al valor medido. Ahora podemos aumentar el tiempo de exposición hasta que el indicador EV vuelve a 0, indicando así que los parámetros actuales resultarían en la misma exposición que teníamos al principio; en nuestro caso significa aumentar el tiempo de exposición desde 15 segundos a 32 minutos. Por último, sólo tienes que pulsar en "Aplicar" para configurar la cámara con estos parámetros, y poner en marcha el guión de larga exposición.

NOTA: El calculador de larga exposición sólo aplicará los valores presentados en la pantalla cuando el tiempo de exposición (Tv) sea de un minuto o más; para tiempos de exposición más cortos, el botón "Aplicar" estará simplemente inactivo.

SUGERENCIA: Si planeas usar un filtro de densidad neutra, puedes medir la escena sin el filtro ND y, a continuación, entrar en el calculador de larga exposición y ajustar la exposición para obtener un resultado Ev inverso al valor del filtro ND. Por ejemplo, suponiendo que tenemos un filtro ND8 (8 pasos de reducción de la luz): si la cámara mide 1/120s f/4.0 ISO1600 sin el filtro, selecciona 2' f/8.0 ISO100 para lograr un EV de +8.

## Calculadora DOF ##

La Calculadora DOF puede ayudar a determinar la profundidad de campo de una escena, o el rango de distancias que serán fotografiados en foco; para obtener más información acerca de este concepto, por favor visita [DOF Master](http://www.dofmaster.com/index.html).

Después de entrar en la calculadora DOF, ajusta la distancia focal de la lente, la apertura que estás utilizando, y la distancia desde la cámara al sujeto. El guión mostrará entonces las distancias próxima y lejana de nitidez aceptable. Ahora puedes cambiar la apertura y/o la distancia de enfoque hasta que la profundidad de campo que se muestra coincida con la parte de la escena que tú consideres importante y quieras que permanezca detro de foco.

Cuando la entrada "Max. DOF (m)" muestra "INF!", se ha alcanzado la distancia hiperfocal, y por lo tanto todo, desde la distancia próxima de enfoque aceptable hasta el infinito estará enfocado.

# Los preajustes (presets) #

Un "preset" (preajuste) es una instantánea completa que contiene todos los ajustes de la cámara y los parámetros de configuración. Los presets se pueden utilizar para pre-configurar la cámara para una situación específica de disparo (como "paisaje", "retrato", "poca luz", "pájaros en vuelo", etc.), y te permiten tener un acceso rápido a estas configuraciones después. Los preajustes son almacenados en la tarjeta CF en sí. Se pueden almacenar hasta 9 preajustes. Sin embargo, el número de preajustes es ilimitado si tenemos en cuenta que puedes utilizar múltiples tarjetas CF cada una de ellas conteniendo hasta 9 preajustes diferentes.

## El modo A-DEP ##

Bajo circunstancias normales, cuando se recupera un preajuste todos los parámetros de la cámara se cambian, incluso el modo AE. Ten en cuenta que la cámara puede entonces operar en un modo de AE que es diferente del modo AE actualmente seleccionado en el dial principal. Pero si se apaga la cámara y se vuelve a encender, se volverá al modo de AE real seleccionado en el dial principal.

Para resolver este asunto, hay una opción para secuestrar el modo A-DEP (mayormente inutilizado). Cuando esa opción está activa, ocurrirán los cambios siguientes:

  * Los presets sólo pueden cargarse cuando la cámara está en el modo A-DEP. Se visualiza la palabra "Presets" en lugar de "A-DEP" en el dial de modo.
  * Cuando la cámara se enciende en el modo A-DEP, o cuando el usuario mueve el dial principal al modo A-DEP, se carga automáticamente el último preset utilizado.

Si esta opción no está activada, cuando se selecciona la posición A-DEP en el dial de modo, la cámara usará el modo A-DEP como lo haría normalmente.

# AutoISO #

400plus soporta AutoISO en los modos creativos, utilizando nuestros propios algoritmos. Funciona mediante la lectura de las mediciones que la cámara hace cuando presionas hasta la mitad el botón de disparo, y cambiando el valor ISO en consecuencia. El comportamiento del AutoISO es diferente para cada modo creativo, pero la idea es llanamente la misma: utilizar la ISO más baja posible para mantener una adecuada velocidad o apertura.

Para habilitar AutoISO para los modos creativos, se debe activar en el menú de ajustes, o presionar el botón de IMPRESIÓN DIRECTA en el cuadro de diálogo de selección de ISO; para desactivarla, utiliza el menú de ajustes o selecciona cualquier valor ISO en el cuadro de diálogo de selección de ISO.

## AutoISO y modo Av ##

La intención del AutoISO en el modo Av es usar el ISO más bajo posible para asegurar que no se produzca desenfoque por movimiento.

En el modo Av normal el usuario selecciona ISO y apertura, y la cámara decide la velocidad de obturación de acuerdo a la escena. Sin embargo, cuando AutoISO está activo, la 400plus seleccionará siempre el ISO más bajo posible (según se haya configurado "Min ISO"), a no ser que la velocidad de obturación sea demasiado baja (según se haya configurado "Min Tv"); cuando esto ocurre, la cámara incrementará automáticamente el valor ISO (hasta "Max ISO") según necesite.

Ten en cuenta que cuando ambos Desplazamiento de Seguridad y AutoISO están habilitados, la velocidad del obturador podría caer por debajo del valor "Min Tv" configurado si se sobrepasa "Max ISO", para mantener la exposición correcta.

## AutoISO y modo Tv ##

En el modo Tv la intención es usar el ISO más bajo posible para asegurar una aceptable profundidad de campo.

En el modo TV, AutoISO tratará de mantener la ISO tan baja como sea posible (tal como está configurada en "Min ISO"), a menos que la escena requiera una apertura mayor que la deseada (como se ha configurado en "Max Av"); por tanto, AutoISO elevará el valor ISO (hasta "Max ISO") según sea necesario.

Por favor, ten en cuenta que debes establecer "Max Av", en general,justo por encima de la máxima apertura de la lente que estés utilizando. Por ejemplo si tu lente es F/4, "Max Av" se debe establecer no inferior a f/5.6; piensa que las lentes zoom pueden tener diferentes aperturas máximas, en función de la distancia focal que estés utilizando. De lo contrario, AutoISO no funcionará adecuadamente en el modo de Tv. Además, el comentario sobre Desplazamiento de Seguridad y AutoISO en el modo Av se aplica también al modo Tv.

## AutoISO y modo P ##

En el modo P, AutoISO _trata de_ comportarse como en el modo Av e incrementa el valor ISO para mantener una mínima velocidad de obturación; pero, dado que la cámara decide tanto la apertura como la velocidad de obturación en este modo, no hay garantías de que aumentar la ISO incremente la velocidad de obturación: tiende a funcionar bien para valores pequeños de "Min Tv", pero para valores más grandes la cámara habitualmente decide cerrar el diafragma en lugar de seleccionar una velocidad de obturación más rápida.

## AutoISO y modo M ##

En el modo M, el comportamiento del AutoISO es totalmente diferente a los otros modos: en este caso el usuario selecciona tanto la apertura como la velocidad de obturación, de modo que 400plus decidirá el ISO correcto para ajustar la escena. Ninguno de los parámetros de configuración afectan al AutoISO en el modo M, y este es el único modo en el que se utilizan valores intermedios de ISO.

Para cambiar la compensación de la exposición en el modo M, utiliza las teclas IZQUIERDA y DERECHA mientras miras por el visor.

# ISO en visor #

Cuando esta opción está activa (puesta en "Sí"), y si la cámara está en cualquier modo creativo, puedes cambiar el valor ISO mientras miras por el visor; en los modos Tv y M, el nuevo valor ISO también se muestra en el visor:

  * Pon la cámara en el modo M o en el modo Tv.
  * Mira a través del visor, y presiona hasta la mitad el botón disparador; deberías ver la medición actual (velocidad de obturación, apertura...).
  * A continuación, pulsa los botones IZQUIERDA y DERECHA para cambiar el valor ISO (o ARRIBA para que aparezca); el nuevo valor se visualiza en el visor, en el mismo lugar donde normalmente se muestra la velocidad de obturación, mientras que el botón esté presionado.
  * En los modos P y Av, el valor ISO también se puede cambiar, pero no se muestra.

**NOTA**: Si la función personalizada "_01 - SET button/Cross keys funct._" está ajustada a "_4 : Cross keys:AF frame Selec._", esta función quedará desactivada, incluso si ha sido habilitada en el menú de ajustes.

# Seleccion del patron AF #

400plus ofrece un rango adicional de selección de puntos del patrón AF, en vez de los sólo dos (selección manual del punto AF y selección automática) que vienen estándar en la cámara. Este modo adicional permite una amplia gama de patrones de selección de puntos múltiples usando diferentes combinaciones de los 9 puntos de enfoque.

Para usar la selección adicional de puntos del patrón AF durante el disparo, pulsa el botón de ZOOM + para entrar en "Selección del punto AF" estándar; a continuación pulsa ZOOM + de nuevo para entrar en el nuevo diálogo "Selección del patrón AF". Usa los botones ARRIBA, ABAJO, IZQUIERDA, DERECHA y SET para desplazarte por los diferentes patrones disponibles, y pulsa hasta la mitad el botón disparador para salir del diálogo.

# Los extras #

Se han agregado a la cámara los siguientes **extras**:

### En la zona básica ###

  * Utiliza el botón AV para alternar entre calidad de imagen RAW, JPEG y RAW+JPEG. Fíjate que la calidad y el tamaño se cambian a "HIGH + L" cada vez que se utiliza esta opción.

### En la zona creativa ###

  * En la pantalla de selección de ISO, pulsa el botón de IMPRESIÓN DIRECTA para activar el [AutoISO](UserGuideSpanish#AutoISO.md). Selecciona cualquier valor ISO para desactivarlo.
  * En el cuadro de diálogo de selección del modo de medición, pulsa IMPRESIÓN DIRECTA para establecer la medición puntual (ver [Notas / Modo de medición puntual](UserGuideSpanish#Modo_de_medicion_puntual.md)).
  * En el cuadro de diálogo de selección del balance de blancos, pulsa IMPRESIÓN DIRECTA para ajustar la temperatura de color definida por el usuario.

# Otros regalos #

Otros cambios en el comportamiento de la cámara, no descritos anteriormente.

## El asunto de la nariz (ojo zurdo) ##

Mientras se mira por el visor, los botones de ISO y WB están inactivos, para prevenir cambios accidentales en los ajustes de la cámara al presionar la nariz o la mejilla del usuario contra el cuerpo de la cámara.

## Soporte mult-idioma ##

Actualmente, 400plus soporta 10 idiomas:

  * Inglés.
  * Finlandés.
  * Francés.
  * Alemán.
  * Húngaro.
  * Italiano.
  * Polaco.
  * Ruso.
  * Chino simplificado.
  * Español.

El deseo es tener 400plus en tantos idiomas como sea posible! Si estás interesado en ayudar en la conversión de 400plus a un idioma diferente, sin duda tu esfuerzo es bienvenido. Háznoslo saber mediante una solicitud a través del foro!

# Notas #

Algunas notas y comentarios.

## La _desparecida_ ISO-3200 ##

Versiones anteriores de 400plus soportaban la ISO-3200; o más precisamente, parecían soportarla: mientras la cámara mostraba "3200" como valor ISO, las imágenes estaban realmente siendo disparadas a ISO-3000. Las últimas versiones de 400plus corrigen este error, y por lo tanto ahora sólo se muestran valores de hasta ISO-3000.

Considera, por tanto, que una imagen tomada a ISO-3000 será exactamente la misma que si hubiera sido disparada con la vieja ISO-3200.

## ISOs Extendidos ##

Los valores ISO no estándar son sólo valores calculados por software, y técnicamente ofrecen poca o ninguna ganancia sobre los disparos a ISOs nativos y el posterior procesado de la imagen.

Ten en cuenta que la cámara no siempre mostrará en la pantalla el valor ISO correcto; por ejemplo, una imagen disparada a ISO 3000 se mostrará como a ISO 3200 durante la revisión.

## Modo de medicion puntual ##

El modo de medición puntual es como el modo de "medición parcial" estándar, pero el área comprendida dentro de la medición es más pequeña (aproximadamente 3.5% del centro del visor frente a la medición parcial de aproximadamente 9% del centro del visor). Funciona bastante bien cuando se necesita.

# Errores conocidos #

Se han comunicado y confirmado los siguientes errores relevantes:

  * [Issue #156](https://code.google.com/p/400plus/issues/detail?id=#156): La ayuda al autofoco no se dispara desde el 430EX cuando se utilizan patrones de AF extendidos.
  * [Issue #153](https://code.google.com/p/400plus/issues/detail?id=#153): El menú estándar parpadea ántes del menú de accesos directos.