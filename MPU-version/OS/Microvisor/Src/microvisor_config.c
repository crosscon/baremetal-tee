#include "microvisor_config.h"
#include <stdint.h>

/* Configuration file to store different settings for the microvisor:
can be customized by the user before the compilation of MCU-Fortifier */

uint8_t Update_Server_IP[] = {192, 168, 1, 168}; // update server IP
uint16_t UPDATE_SERVER_PORT = 4433;              // update server port
uint16_t LOCAL_PORT = 25565;                     // random local port

/* Shared communication key for secure communication with Update Server */
const uint8_t Update_Server_Key[32] = "this is the 32 bytes shared key!";