#ifndef __WIFI_WRAPPER_H
#define __WIFI_WRAPPER_H

#include "wifi.h"

#define WIFI_CONNECTION_NAME "Connection"
#define WIFI_RECV_TIMEOUT 3000
#define WIFI_SEND_TIMEOUT 3000
#define WIFI_MAX_ATTEMPTS                                                      \
  1000 // Maximum number of WIFI_ReceiveData() calls before giving up

/**
 * @brief  Opens a TCP connection to the specified server
 * @param socket: socket (0-3) selected
 * @param  ipaddr : IP address of the target server
 * @param  port : port of the target server
 * @param  local_port : local port used for connection
 * @retval Operation status WIFI_STATUS_OK if the connection was opened
 * succesfully, WIFI_STATUS_ERROR otherwise
 */
WIFI_Status_t wifi_wrapper_open_client_connection(uint32_t socket,
                                                  uint8_t *ipaddr,
                                                  uint16_t port,
                                                  uint16_t local_port);

/**
 * @brief  Closes previously opened TCP connection
 * @param socket: socket (0-3) selected
 * @retval Operation status WIFI_STATUS_OK if the connection was closed
 * succesfully, WIFI_STATUS_ERROR otherwise
 */
WIFI_Status_t wifi_wrapper_close_client_connection(uint32_t socket);

/**
 * @brief  Performs all-or-nothing data receive from socket
 *
 * Attempts to perform WIFI_ReceiveData multiple times
 * until either one of the following conditions is met:
 * - all of the data has arrived (function returns WIFI_STATUS_OK)
 * - only partial data arrived and attempts exhausted (function returns
 * WIFI_STATUS_ERROR)
 * - error encountered during receive (function returns WIFI_STATUS_ERROR)
 * @param socket: socket (0-3) selected
 * @param pdata : pointer to Rx buffer
 * @param Reqlen : maximum length of the data to be received
 * @retval Operation status WIFI_STATUS_OK when all data requested was recevied,
 * WIFI_STATUS_ERROR when partial data recevied or error
 */
WIFI_Status_t wifi_wrapper_receive_data(uint32_t socket, uint8_t *pdata,
                                        uint16_t Reqlen);

/**
 * @brief  Performs all-or-nothing data send from socket
 *
 * Attempts to perform WIFI_SendData multiple times
 * until either one of the following conditions is met:
 * - all of the data has been sent (function returns WIFI_STATUS_OK)
 * - only partial data has been sent and attempts exhausted (function returns
 * WIFI_STATUS_ERROR)
 * - error encountered during receive (function returns WIFI_STATUS_ERROR)
 * @param socket: socket (0-3) selected
 * @param pdata : pointer to data to send
 * @param Reqlen : maximum length of the data to be sent
 * @retval Operation status WIFI_STATUS_OK when all data requested was recevied,
 * WIFI_STATUS_ERROR when partial data recevied or error
 */
WIFI_Status_t wifi_wrapper_send_data(uint32_t socket, uint8_t *pdata,
                                     uint16_t Reqlen);

#endif /* __WIFI_WRAPPER_H */