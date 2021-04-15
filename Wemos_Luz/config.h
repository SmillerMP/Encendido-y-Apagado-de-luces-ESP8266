/************************ Configuracion IO Adafruit  *******************************/

// Ingresar su cuenta y su IO KEY de IO Adafuit
#define IO_USERNAME    "SamuelIMP"
#define IO_KEY         "aio_Bbqv34zChTNDe0PC0u7IlxkTmJTM"

/******************************* Configuration WIFI  **************************************/

//Igresar nombre de su red WiFi y contraseña
#define WIFI_SSID       "TURBONETT_4C70C4"  // <---- nombre de red
#define WIFI_PASS       "10E8818E46" // <---- contraseña de red

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
