/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private defines -----------------------------------------------------------*/
/* Update SSID and PASSWORD with own Access point settings */
#define SSID		"OpenWrt"
#define PASSWORD	"cavallari"
#define PORT		80

#define WIFI_WRITE_TIMEOUT	10000
#define WIFI_READ_TIMEOUT	10000
#define SOCKET				0

/* Private typedef------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t	http[1024];
static uint8_t	IP_Addr[4];
static int		LedState = 0; 

// capital_elevation: Paris, Rome, Madrid, Berlin, London, Bern
const uint32_t capital_elevation[] = {34, 14, 667, 34, 14, 542};

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static WIFI_Status_t SendWebPage(bool selection, uint32_t index, bool is_led_on);
static int wifi_server(void);
static int wifi_start(void);
static int wifi_connect(void);
static bool WebServerProcess(void);

/* Private functions ---------------------------------------------------------*/
int main(void) {
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Configure LED2 */
	BSP_LED_Init(LED2);

	wifi_server();

	while(1);
}

static int wifi_start(void) {
	uint8_t	MAC_Addr[6];

 	/*Initialize and use WIFI module */
	if(WIFI_Init() == WIFI_STATUS_OK)	{
		if(WIFI_GetMAC_Address(MAC_Addr) != WIFI_STATUS_OK)
			return -1;
	} else {
		return -1;
	}
	return 0;
}

int wifi_connect(void) {

	wifi_start();

	if( WIFI_Connect(SSID, PASSWORD, WIFI_ECN_WPA2_PSK) == WIFI_STATUS_OK) {
		if(WIFI_GetIP_Address(IP_Addr) != WIFI_STATUS_OK) {
			return -1;
		}
	} else {
		 return -1;
	}
	return 0;
}

int wifi_server(void) {
	bool stop_server = false;

	if (wifi_connect() != 0) return -1;

	if (WIFI_STATUS_OK != WIFI_StartServer(SOCKET, WIFI_TCP_PROTOCOL, 1, "", PORT))
		return -1;

	// serving requests loop
	do {
		uint8_t RemoteIP[4];
		uint16_t RemotePort;

		while (WIFI_STATUS_OK != WIFI_WaitServerConnection(SOCKET,1000,RemoteIP,&RemotePort));	// waiting for connection

		stop_server=WebServerProcess();

		if(WIFI_CloseServerConnection(SOCKET) != WIFI_STATUS_OK)
			return -1;
	} while(stop_server == false);

	if (WIFI_STATUS_OK != WIFI_StopServer(SOCKET))
		return 1;

	return 0;
}

static bool WebServerProcess(void) {
	uint16_t respLen;
	static uint8_t resp[1024];
	bool stop_server=false;
	bool selected = false;
	uint32_t selection_value = 0;

	if (WIFI_STATUS_OK == WIFI_ReceiveData(SOCKET, resp, 1000, &respLen, WIFI_READ_TIMEOUT)) {
		if(respLen > 0)  {
			if(strstr((char *)resp, "GET")) {	// GET request
				SendWebPage(0, 0, LedState);
			} else if(strstr((char *)resp, "POST")) {	// POST request
				// parsing radio button value
				if(strstr((char *)resp, "radio")) {
					if(strstr((char *)resp, "radio=0")) {
						LedState = 0;
						BSP_LED_Off(LED2);
					} else if(strstr((char *)resp, "radio=1")) {
						LedState = 1;
						BSP_LED_On(LED2);
					}
				}
				// parsing stop server command
				if(strstr((char *)resp, "stop_server")) {
					if(strstr((char *)resp, "stop_server=0")) {
						stop_server = false;
					} else if(strstr((char *)resp, "stop_server=1")) {
						stop_server = true;
					}
				}
				// parsing selection value
				char* selection = strstr((char *)resp, "selection=");
				selection = selection + strlen("selection=");	// scroll to beginning of value
				uint8_t digit_num = strspn(selection, "0123456789");	// count digits
				if(digit_num > 0) {
					char* end;
					selection_value = strtol(selection, &end, 10);
					selected = true;
				}

				SendWebPage(selected, selection_value, LedState);
			 }
		}
	}
	return stop_server;
}

static WIFI_Status_t SendWebPage(bool selection, uint32_t index, bool is_led_on) {
	uint8_t	temp[50];
	uint16_t SentDataLength;
	WIFI_Status_t ret;

	/* construct web page content */
	strcpy((char *)http, (char *)"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n");
	strcat((char *)http, (char *)"<html>\r\n<body>\r\n");
	strcat((char *)http, (char *)"<title>STM32L475</title>\r\n");
	strcat((char *)http, (char *)"<h2>Web Server vulnerable to Buffer Overread attack</h2>\r\n");
	strcat((char *)http, (char *)"<br><hr>\r\n");
	strcat((char *)http, (char *)"<p><span>What's the elevation of these European Capitals?</span><br>");
	strcat((char *)http, (char *)"<span>[0 Paris, 1 Rome, 2 Madrid, 3 Berlin, 4 London, 5 Bern]</span></p>");
	strcat((char *)http, (char *)"<form method=\"POST\"><strong>");
	strcat((char *)http, (char *)"<p><input type=\"text\" name=\"selection\" value=\"");
	if(selection) {
		sprintf((char *)temp, "%d", (int) index);
		strcat((char *)http, (char *)temp);
	}
	strcat((char *)http, (char *)"\" > Select a capital (0-5)");

	if (is_led_on) {
		strcat((char *)http, (char *)"<p><input type=\"radio\" name=\"radio\" value=\"0\" >LED off");
		strcat((char *)http, (char *)"<br><input type=\"radio\" name=\"radio\" value=\"1\" checked>LED on");
	} else {
		strcat((char *)http, (char *)"<p><input type=\"radio\" name=\"radio\" value=\"0\" checked>LED off");
		strcat((char *)http, (char *)"<br><input type=\"radio\" name=\"radio\" value=\"1\" >LED on");
	}
	strcat((char *)http, (char *)"</strong><p><input type=\"submit\"></form></span>");

	if(selection) {
		strcat((char *)http, (char *)"<br><hr>\r\n");
		strcat((char *)http, (char *)"<p><h5>Output</h5>");
		strcat((char *)http, (char *)"<br><span>The elevation of the selected capital is: ");
		sprintf((char *)temp, "%d", (int) capital_elevation[index]);
		strcat((char *)http, (char *)temp);
		strcat((char *)http, (char *)"</span></p>");

		strcat((char *)http, (char *)"<br><hr>\r\n");
		strcat((char *)http, (char *)"<p><h5>Advanced Information</h5>");
		strcat((char *)http, (char *)"<table><tr><th>Description</th><th>Value</th></tr>");
		
		strcat((char *)http, (char *)"<tr><td>Elevation (dec)</td><td>");
		sprintf((char *)temp, "%d", (int) capital_elevation[index]);
		strcat((char *)http, (char *)temp);

		strcat((char *)http, (char *)"</td></tr><tr><td>Elevation (hex)</td><td>");
		sprintf((char *)temp, "%#.8x", (int) capital_elevation[index]);
		strcat((char *)http, (char *)temp);
		strcat((char *)http, (char *)"</td></tr><tr><td>Accessed address</td><td>");
		sprintf((char *)temp, "%#.8x", (int) &capital_elevation[index]);
		strcat((char *)http, (char *)temp);
		strcat((char *)http, (char *)"</td></tr></table></p>");
	}

	strcat((char *)http, (char *)"</body>\r\n</html>\r\n");

	ret = WIFI_SendData(0, (uint8_t *)http, strlen((char *)http), &SentDataLength, WIFI_WRITE_TIMEOUT);

	if((ret == WIFI_STATUS_OK) && (SentDataLength != strlen((char *)http))) {
		ret = WIFI_STATUS_ERROR;
	}

	return ret;
}

static void SystemClock_Config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* MSI is enabled after System reset, activate PLL with MSI as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 40;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLP = 7;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		/* Initialization Error */
		while(1);
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
		 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
		/* Initialization Error */
		while(1);
	}
}

/**
* @brief	EXTI line detection callback.
* @param	GPIO_Pin: Specifies the port pin connected to corresponding EXTI line.
* @retval None
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	switch (GPIO_Pin)
	{
		case (GPIO_PIN_1):
		{
			SPI_WIFI_ISR();
			break;
		}
		default:
		{
			break;
		}
	}
}

/**
* @brief	SPI3 line detection callback.
* @param	None
* @retval None
*/
void SPI3_IRQHandler(void) {
	HAL_SPI_IRQHandler(&hspi);
}