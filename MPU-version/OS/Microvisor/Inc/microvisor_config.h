#ifndef __MICROVISOR_CONFIG_H
#define __MICROVISOR_CONFIG_H

/* Generic MCU Configuration */
#define LICENSE_LEN 32
extern const uint8_t license[LICENSE_LEN];	// MCU-Fortifier license
extern const uint32_t firmware_size;	// user application size

/* Network Connection Configuration */
#define SSID		"OpenWrt"
#define PASSWORD	"cavallari"

/* Update Server Connection Configuration */
#define READ_TIMEOUT 3000	// socket read timeout in ms
#define UPDATE_SERVER_CN "MCU-Fortifier Update Server"	// Common Name of update server, must equal the one stored in the server certificate
extern uint8_t Update_Server_IP[];	// update server IP
extern uint16_t UPDATE_SERVER_PORT;	// update server port
extern uint16_t LOCAL_PORT;
extern const uint8_t Update_Server_Key[32];	// 128 bit shared communication key

#endif /* __MICROVISOR_CONFIG_H */