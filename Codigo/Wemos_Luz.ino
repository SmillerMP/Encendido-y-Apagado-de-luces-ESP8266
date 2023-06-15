
#include "config.h"

/************************ Programa Principal *******************************/

//Incluir librerias
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

//definicion del boton en el control
#define boton 0xE318261B // <----- Codigo del boton


// ------- Variables de la placa ---------
// rele en el pin D2
const int rele = D2;

// Pulsador en el Pin D3
const int pulsador = D3;

// Recptor control/mando en el pin D5
const uint16_t recep = D5;

IRrecv irrecv(recep);
decode_results results;

// Variable que ayuda a sincronizar el server y la placa
bool estado = false;
// ----------------------------------------

// se elije que feed se mandaran los comandos o datos
AdafruitIO_Feed *command = io.feed("NOMBRE_DEL_FEED"); // <------------- nombre del feed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void setup() {

  // Inicia la conexion serial
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  pinMode(rele, OUTPUT);
  pinMode(pulsador, INPUT_PULLUP);

  // PIN D0 controla la luz presente en la placa
  pinMode(D0, OUTPUT);
  
  // Conexion de con el servidor
  Serial.print("Conectando con Adafruit IO");
  io.connect();

  
  /* esta funcion aparece siempre que IO Adafruit
  reciba un nuevo mensaje*/
  command->onMessage(handleMessage);

  
  //Esperando conexion
  while(millis() < 12000) {
    Serial.print(".");
    digitalWrite(D0, LOW);
    delay(500);
    digitalWrite(D0, HIGH);
    }

  if (io.status() == AIO_CONNECTED){
     //Conectado
    Serial.println();
    Serial.println("Conexion exitosa con Adafuit IO"); 
    command->save(0);
  }else{
    Serial.println();
    Serial.print("Error en la conexion");
  }

  irrecv.enableIRIn();
  
}

void loop() {


  /* Siempre debe estar en la parte superior del bucle
     Mantiene la comunicacion entre la placa y el servidor
     IO Adafruit procesa los datos entrantes*/
  if (io.status() == AIO_CONNECTED){
    io.run();
  }

  //codigo para el pulsador
  if (digitalRead(pulsador) == LOW) { 
    //digitalWrite(rele, !digitalRead(rele));
    if (estado == false){
      digitalWrite(rele, HIGH);
      command->save(1);
      estado = true;
    }
    else{
      digitalWrite(rele, LOW);
      command->save(0);
      estado = false;
    }
    delay(250);
  }   

  //codigo para el receptor infrarrojo
  if (irrecv.decode(&results)) {
    serialPrintUint64(results.value, HEX);
    Serial.println();
    if (results.value == boton){
      //digitalWrite(rele, !digitalRead(rele));
      if (estado == false){
      digitalWrite(rele, HIGH);
      command->save(1);
      estado = true;
      }
      else{
        digitalWrite(rele, LOW);
        command->save(0);
        estado = false;
      }
      delay(200);
      }
    irrecv.resume(); 
    }  
 }



/* Esta funcion se manda a llamar siempre que recibe 
un mensaje "comando" de parte del servidor de 
IO Adafruit*/
void handleMessage(AdafruitIO_Data *data) {

  int command = data->toInt();

  if (command == 1){ 
    Serial.print("recibido <- ");
    Serial.println(command);
    digitalWrite(rele, HIGH);
    estado = true;
  } else {
    Serial.print("recibido <- ");
    Serial.println(command);
    digitalWrite(rele, LOW);
    estado = false;
  }
 
}

//CREDITOS:
//Adafuit IO
//Samuel IMP  (Smiller MP)