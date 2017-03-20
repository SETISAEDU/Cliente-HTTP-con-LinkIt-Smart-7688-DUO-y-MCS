# Cliente-HTTP-con-LinkIt-Smart-7688-DUO-y-MCS

Al poseer una arquitectura similar a la del Arduino Yún, la LinkIt Smart 7688 DUO puede cargar sketchs de Arduino y utilizar la MT7688 como un medio de conexión a Internet gracias al `Bridge` tambien facilitando la comunicacion entre la distro de Linux Open WRT y Arduino.

# Subiendo variables a la nube MCS con librería Bridge

Este ejemplo es un ejemplo sencillo que conecta LinkIt Smart 7688 Duo a un dispositivo MCS con la librería Bridge de Arduino.

Dado que LinkIt Smart 7688 Duo es algo compatible con la librería **Bridge** de Arduino, podemos usar la librería de bridge para conectarnos a MCS con IDE de Arduino.

## Habilitando la librería Bridge

Utilizando los siguientes comandos vamos a habilitar la librería Bridge on la LinkIt Smart 7688 DUO:

```
uci set yunbridge.config.disable='0'
uci commit
reboot
```
Solo es necesario llevar a cabo esto una vez. 

# Ajustando MCS

[Mediatek Cloud Sandbox](https://mcs.mediatek.com/) es un servidor Web que nos permite crear stream de datos que son subidos por la LinkIt Smart 7688 DUO y así poder monitorear los diferentes datos subidos a dicho servidor. 

Prepare y ajuste el prototipo MCS y dispositivos de prueba siguienndo el presente [tutorial](https://mcs.mediatek.com/resources/latest/tutorial).

![Mediatek Cloud Sandbox]()

## Importando el proyecto del Dispositivo de Prueba

Sin tener que hacer todos los pasos podemos importar el proyecto para apreciar todas las configuraciones hechas. Tenemos que importar el archivo `TestDevice.json`

# Esquema de conexión del proyecto

Conecte los elementos como se describe en la suguiente imagen:
![LinkIt Smart 7688 DUO y DHT11](https://raw.githubusercontent.com/SETISAEDU/Cliente-HTTP-con-LinkIt-Smart-7688-DUO-y-MCS/master/Diagrama_LinkIt_Parte%20III.png)

# Conectar la LinkIt Smart 7688 DUO a Internet

Por favor, refierase a la guía de usuario del desarrollador para ajustar apropiadamente la conección WiFi de la LinkIt Smart 7688 DUO. Esto provee conexión a Internet y acceso al servicio de MCS.

# Sketch de Arduino

Subimos de el Arduino IDE el sktech llamado `LinkItDHT11_MCS.ino` Este código hará las lecturas de temperatura y humedad del sensor DHT11 y los subira a MCS cada dos segundos.

# Freeboard
[Freeboard](https://freeboard.io/) es una muy buena alternativa visual en donde podremos apreciar nuestras variables subidas a la nube. Cuenta con muchas maneras de desplegar información ya sea de temperatura, humedad, posición geosatelital y hasta videostreaming desde una sola consola. 

![Proyecto en Freeboard]()
