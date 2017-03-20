// Librerías de comunicación entre el MT7688 y el ATmega32u4
#include <Bridge.h>
#include <HttpClient.h>
#include <BridgeClient.h>

// Librería del DHT11
#include "DHT.h"

// Variables de definición para el Mediatek Cloud Sandbox
#define DEVICEID "DmN8XE3D" // Introduce tu deviceId
#define DEVICEKEY "7NdXUJNfqUpqZW6Z" // Introduce tu deviceKey
#define SITE_URL "api.mediatek.com"

// Pin de datos y el tipo de sensor a utilizar
#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11

// Número de pines para los LEDs indicadores
#define Conectado 4
#define Reporte 5
#define Subiendo 6

// Variables globales de trabajo
static unsigned long beat = 0;
static String commandServer;
static int commandPort = 0;
int ret;

float h;
float t;
static unsigned long measure = 0;

// Esto será utilizado para conectar al servidor
BridgeClient bc;

// Configuración del sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(Conectado, OUTPUT);
  pinMode(Reporte, OUTPUT);
  pinMode(Subiendo, OUTPUT);

  // Inicialización del bridge y el DHT11
  Bridge.begin();
  dht.begin();

  // Rutina de conexión al servidor
  getCommandServer();
  beat = millis();
  measure = millis();
}

void getCommandServer()
{
  // Prepara los cabezales para la auntentificacion de la API de MCS
  String header = "deviceKey: ";
  header += DEVICEKEY;
  header += "\r\n";
  header += "Connection: close";

  HttpClient c;
  c.setHeader(header);
  c.get(SITE_URL "/mcs/v2/devices/" DEVICEID "/connections.csv");
  c.setTimeout(1000);

  const String resp = c.readString();
  const int sep = resp.indexOf(',');
  if (-1 == sep)
  {
    // Una vez establecida la conexión enciende el LED verde
    digitalWrite(Conectado, LOW);
    return;
  }
  digitalWrite(Conectado, HIGH);
}

void heartBeat(Client &c) {
  // Manda un dato de Heart beat
  // format reference: https://mcs.mediatek.com/resources/latest/api_references/#get-connection
  static const char* heartbeat = DEVICEID "," DEVICEKEY ",0";
  c.println(heartbeat);
  c.println();
  delay(100);
}

void loop() {

  // Mnada un heart beat cada cinco segundos;
  // o la conexión será cerrada por el servidor.
  if (5000 < (millis() - beat)) {
    heartBeat(bc);
    beat = millis();
    digitalWrite(Reporte, HIGH);
    delay(300);
    digitalWrite(Reporte, LOW);
  }

  // Sube los valores de la temperatura y la humedad al MCS.
  if (2000 < (millis() - measure)) {
    h = dht.readHumidity();
    t = dht.readTemperature();
    upload_measure1(t);
    upload_measure2(h);
    measure = millis();
    digitalWrite(Subiendo, HIGH);
    delay(300);
    digitalWrite(Subiendo, LOW);
  }
}

void upload_measure1(int temp) {

  String str_temp = String(temp);
  String upload_temp = "DHT11_Temp,," + str_temp;

  // Prepare HTTP header for MCS API authentication.
  // note that we don't have to add content-length and content-type.
  // these will be automatically added by HttpClient (with curl).
  //
  // !We must put Content-Type in the first line to prevent
  // curl from sending "application/x-www-form-urlencoded"
  // as content-type. MCS blocks "application/x-www-form-urlencoded"
  // just like many web services.
  String header = "Content-Type: text-csv\r\n";
  header += "deviceKey: ";
  header += DEVICEKEY;
  header += "\r\n";
  header += "Connection: close";

  // refer to https://mcs.mediatek.com/resources/latest/api_references/#upload-data-points
  HttpClient http;
  http.setHeader(header);
  http.post(SITE_URL "/mcs/v2/devices/" DEVICEID "/datapoints.csv", upload_temp.c_str());
  http.setTimeout(1000);

  delay(300);
}

void upload_measure2(int hum) {

  String str_hum = String(hum);
  String upload_hum = "DHT11_Hum,," + str_hum;

  // Prepare HTTP header for MCS API authentication.
  // note that we don't have to add content-length and content-type.
  // these will be automatically added by HttpClient (with curl).
  //
  // !We must put Content-Type in the first line to prevent
  // curl from sending "application/x-www-form-urlencoded"
  // as content-type. MCS blocks "application/x-www-form-urlencoded"
  // just like many web services.
  String header = "Content-Type: text-csv\r\n";
  header += "deviceKey: ";
  header += DEVICEKEY;
  header += "\r\n";
  header += "Connection: close";

  // refer to https://mcs.mediatek.com/resources/latest/api_references/#upload-data-points
  HttpClient http;
  http.setHeader(header);
  http.post(SITE_URL "/mcs/v2/devices/" DEVICEID "/datapoints.csv", upload_hum.c_str());
  http.setTimeout(1000);

  delay(300);
}

void Alert() {
  digitalWrite(Conectado, HIGH);
  delay(300);
  digitalWrite(Conectado, LOW);
}
