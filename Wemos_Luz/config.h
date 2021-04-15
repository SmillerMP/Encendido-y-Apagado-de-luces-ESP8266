/************************ Configuracion IO Adafruit  *******************************/

// Ingresar su cuenta y su IO KEY de IO Adafuit
#define IO_USERNAME    "TU_USUARIO"  // <-------- usuario de cuenta IO Adafruit 
#define IO_KEY         "TU_TOKE"  // <-------- Clave o Token de cuenta IO Adafruit

/******************************* Configuration WIFI  **************************************/

//Igresar nombre de su red WiFi y contraseña
#define WIFI_SSID       "TU_RED"  // <---- nombre de red
#define WIFI_PASS       "TU_CONTRASEÑA" // <---- contraseña de red

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
