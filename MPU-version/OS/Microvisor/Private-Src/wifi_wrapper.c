#include "wifi_wrapper.h"

WIFI_Status_t wifi_wrapper_open_client_connection(uint32_t socket,
                                                  uint8_t *ipaddr,
                                                  uint16_t port,
                                                  uint16_t local_port) {
  return WIFI_OpenClientConnection(socket, WIFI_TCP_PROTOCOL,
                                   WIFI_CONNECTION_NAME, ipaddr, port,
                                   local_port);
}

WIFI_Status_t wifi_wrapper_close_client_connection(uint32_t socket) {
  return WIFI_CloseClientConnection(socket);
}

WIFI_Status_t wifi_wrapper_receive_data(uint32_t socket, uint8_t *pdata,
                                        uint16_t Reqlen) {
  uint32_t attempts = WIFI_MAX_ATTEMPTS;
  uint16_t remaining_bytes = Reqlen;
  uint16_t read_bytes = 0;

  while (attempts > 0) {
    uint32_t result =
        WIFI_ReceiveData(socket, &pdata[read_bytes], remaining_bytes,
                         &read_bytes, WIFI_RECV_TIMEOUT);
    attempts--;
    if (result == WIFI_STATUS_OK) {
      remaining_bytes -= read_bytes;
      if (remaining_bytes == 0)
        return WIFI_STATUS_OK;
    } else {
      break;
    }
  }
  return WIFI_STATUS_ERROR;
}

WIFI_Status_t wifi_wrapper_send_data(uint32_t socket, uint8_t *pdata,
                                     uint16_t Reqlen) {
  uint32_t attempts = WIFI_MAX_ATTEMPTS;
  uint16_t remaining_bytes = Reqlen;
  uint16_t sent_bytes = 0;

  while (attempts > 0) {
    uint32_t result = WIFI_SendData(socket, &pdata[sent_bytes], remaining_bytes,
                                    &sent_bytes, WIFI_SEND_TIMEOUT);
    attempts--;
    if (result == WIFI_STATUS_OK) {
      remaining_bytes -= sent_bytes;
      if (remaining_bytes == 0)
        return WIFI_STATUS_OK;
    } else {
      break;
    }
  }
  return WIFI_STATUS_ERROR;
}