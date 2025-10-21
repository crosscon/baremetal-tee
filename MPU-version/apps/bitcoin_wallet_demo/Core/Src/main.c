/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tee_client_api.h"
#include "tx.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RNG_HandleTypeDef hrng;

UART_HandleTypeDef huart1;


/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_RNG_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int __io_putchar(int ch){
    HAL_UART_Transmit(&huart1, (uint8_t *) &ch, 1, HAL_MAX_DELAY);
    return ch;
}

void rng_init(void)
{
	/* Enable RNG clock source */
	__HAL_RCC_RNG_CLK_ENABLE();

	/* RNG Peripheral enable */
	RNG->CR |= RNG_CR_RNGEN;
}

void rng_deinit(void)
{
	/* Disable RNG peripheral */
	RNG->CR &= ~RNG_CR_RNGEN;

	/* Disable RNG clock source */
	__HAL_RCC_RNG_CLK_DISABLE();
}

uint32_t rng_get(void)
{
	/* Wait until one RNG number is ready */
	while (!(RNG->SR & (RNG_SR_DRDY)));

	/* Get a 32-bit Random number */
	return RNG->DR;
}

// Declaration of the prototypes of Bitcoin Wallet functions used by the client
static TEEC_Result ta_bitcoin_cmd_check_masterkey(TEEC_Session sess, uint32_t pin, uint32_t cmd_id, uint32_t err_origin);
static TEEC_Result ta_bitcoin_cmd_generate_new_masterkey(TEEC_Session sess, uint32_t pin, uint32_t cmd_id, uint32_t err_origin, char* mnemonic);
static TEEC_Result ta_bitcoin_cmd_mnemonic_to_masterkey(TEEC_Session sess, uint32_t pin, uint32_t cmd_id, uint32_t err_origin, char* mnemonic);
static TEEC_Result ta_bitcoin_cmd_erase_masterkey(TEEC_Session sess, uint32_t pin, uint32_t cmd_id, uint32_t err_origin);
static TEEC_Result ta_bitcoin_cmd_issue_transactions(TEEC_Session sess, uint32_t pin, uint32_t cmd_id, uint32_t err_origin, uint32_t i);
static TEEC_Result ta_bitcoin_cmd_get_bitcoin_address(TEEC_Session sess, uint32_t pin, uint32_t cmd_id, uint32_t err_origin, uint32_t account_id);

// Custom function to print uint8_t array
static void print_uint8(uint8_t* array, uint32_t array_len){
	uint32_t i;
	for(i=0; i<array_len; i++){
		printf("%x", array[i]);
	}
	printf("\n");
}

// Number of different commands that the client can send to the Bitcoin Wallet TA
#define COMMAND_IDS_LEN     6

// Sequence of commands that the client will send to the Bitcoin Wallet TA
unsigned int command_ids[] = {TA_BITCOIN_WALLET_CMD_2,   //Generate master key
                              TA_BITCOIN_WALLET_CMD_1, // Check master key
                              TA_BITCOIN_WALLET_CMD_3, // Mnemonic to master key
                              TA_BITCOIN_WALLET_CMD_5, // Sign transaction
                              TA_BITCOIN_WALLET_CMD_6, // Get bitcoin address
                              TA_BITCOIN_WALLET_CMD_4}; // Erase master key


static TEEC_Result ta_bitcoin_cmd_generate_new_masterkey(TEEC_Session sess, uint32_t pin, uint32_t cmd_id, uint32_t err_origin, char *mnemonic){
	TEEC_Operation op = {0};
	TEEC_Result res;

	printf("Generating new master key...\r\n");
	// Defining the parameter value sent to TA, the parameter are
	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_MEMREF_TEMP_OUTPUT , TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = pin;
	op.params[0].value.b = 0; // 0---unchecked, 1---correct pin, 2---incorrect pin
	op.params[1].tmpref.buffer = malloc(240);
	op.params[1].tmpref.size = 240;

	res = TEEC_InvokeCommand(&sess, cmd_id, &op, &err_origin);
	if (res != TEEC_SUCCESS) {
		ERR_MSG("TEEC_InvokeCommand failed with code 0x%x origin 0x%x\r\n", res, err_origin);
	}

	if (op.params[0].value.b == 2) {
		ERR_MSG("Incorrect pin\r\n");
	}

	if (res == TEEC_SUCCESS){
		printf("\rHere's your wallet mnemonic!\r\n");
		printf("*%s*\n", (char*)op.params[1].tmpref.buffer);
		for (uint8_t i = 0; i < strlen(op.params[1].tmpref.buffer); i++)
		{
			mnemonic[i] = *((char*) (op.params[1].tmpref.buffer) + i);
		}
		printf("\n");
		memset(op.params[1].tmpref.buffer, 0, op.params[1].tmpref.size);
	}
	return TEEC_SUCCESS;
}

static TEEC_Result ta_bitcoin_cmd_mnemonic_to_masterkey(TEEC_Session sess, uint32_t pin, uint32_t cmd_id, uint32_t err_origin, char* mnemonic){
	TEEC_Operation op;
	TEEC_Result res;

	// Clear the TEEC_Operation struct, same as clearing parameter type
	memset(&op, 0, sizeof(op));

	printf("Deriving master key from your mnemonic...\r\n");
	// Defining the parameter value sent to TA, the parameter are
	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_MEMREF_TEMP_INPUT , TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = pin;
	op.params[0].value.b = 0; // 0---unchecked, 1---correct pin, 2---incorrect pin
	op.params[1].tmpref.buffer = mnemonic;
	op.params[1].tmpref.size = strlen(mnemonic);

	res = TEEC_InvokeCommand(&sess, cmd_id, &op, &err_origin);
	if (res != TEEC_SUCCESS) {
		ERR_MSG("TEEC_InvokeCommand failed with code 0x%x origin 0x%x\r\n", res, err_origin);
	}
	if (op.params[0].value.b == 2) {
		ERR_MSG("Incorrect pin\r\n");
	}
	if (res == TEEC_SUCCESS){
		printf("Success!\r\n");
	}
	return TEEC_SUCCESS;
}

static TEEC_Result ta_bitcoin_cmd_check_masterkey(TEEC_Session sess, uint32_t pin, uint32_t cmd_id, uint32_t err_origin){
	TEEC_Operation op;
	TEEC_Result res;

	// Clear the TEEC_Operation struct, same as clearing parameter type
	memset(&op, 0, sizeof(op));

	printf("\rCheck if there's a existing master key...\r\n");
	// Defining the parameter value sent to TA, the parameter are
	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_VALUE_OUTPUT , TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = pin;
	op.params[0].value.b = 0; // 0---unchecked, 1---correct pin, 2---incorrect pin

	res = TEEC_InvokeCommand(&sess, cmd_id, &op, &err_origin);
	if (res != TEEC_SUCCESS) {
		ERR_MSG("TEEC_InvokeCommand failed with code 0x%x origin 0x%x\r\n", res, err_origin);
	}
	if (op.params[0].value.b == 2) {
		ERR_MSG("Incorrect pin\r\n");
	}

	if(op.params[1].value.a == 1)
		printf("Master key exists\r\n");
	else
		printf("None master key exits\r\n");

	return TEEC_SUCCESS;
}

static TEEC_Result ta_bitcoin_cmd_erase_masterkey(TEEC_Session sess, uint32_t pin, uint32_t cmd_id, uint32_t err_origin){
	TEEC_Operation op;
	TEEC_Result res;

	// Clear the TEEC_Operation struct, same as clearing parameter type
	memset(&op, 0, sizeof(op));

	printf("Check if there's a existing master key...\r\n");
	// Defining the parameter value sent to TA, the parameter are
	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_VALUE_OUTPUT , TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = pin;
	op.params[0].value.b = 0; // 0---unchecked, 1---correct pin, 2---incorrect pin

	res = TEEC_InvokeCommand(&sess, cmd_id, &op, &err_origin);
	if (res != TEEC_SUCCESS) {
		ERR_MSG("TEEC_InvokeCommand failed with code 0x%x origin 0x%x\r\n", res, err_origin);
	}
	if (op.params[0].value.b == 2) {
		ERR_MSG("Incorrect pin\r\n");
	}

	if(op.params[1].value.a == 1)
		printf("Master key exists, erase success\r\n");
	else
		printf("None master key exits\r\n");

	return TEEC_SUCCESS;
}

static TEEC_Result ta_bitcoin_cmd_issue_transactions(TEEC_Session sess, uint32_t pin, uint32_t cmd_id, uint32_t err_origin, uint32_t account_id){

	TEEC_Operation op;
	TEEC_Result res;

	/* We hardcode some previous transaction hashses to use for demo purposes */
	const uint8_t prvh[] = {0xdf,0x0b,0x6a,0xfa,0xf0,0xde,0xcd,0x00,0x27,0x80,0xb2,
							0x91,0x16,0x3c,0xad,0xdb,0x76,0x57,0x5f,0xf5,0x5f,0x62,
							0xb1,0x19,0xa2,0x0f,0xda,0x07,0x2f,0x2c,0x47,0xb9};

	const uint8_t tmpsig[] = {OP_DUP,OP_HASH160,0x46,0x2c,0x22,0x2c,0xba,0xac,0x40,
							  0x9f,0x77,0x3b,0x4c,0x0e,0xca,0x99,0x19,0x04,0xc2,0xbb,
							  0x20,0x73,OP_EQUALVERIFY};

	/* Transaction value 0.005555 BTC or 0x15b3 hex */
	//const uint8_t txval[] = {0x62, 0x64, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
	const uint8_t txval[] = {0xB3, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t *out;

	INTX intx = NULL;
	OUTTX outtx = NULL;
	TX tx = NULL;
	TXBUF buf = NULL;

	intx = new_intx(prvh, tmpsig);
	outtx = new_outtx(txval, tmpsig);
	tx = new_tx(intx, outtx);
	buf = new_txbuf();
	out = malloc(72);

	//print_tx(tx);
	serialize_tx(tx, buf);
	//print_ser_bytes(buf);
	printf("Sending transaction for signing.\n");

	// Clear the TEEC_Operation struct, same as clearing parameter type
	memset(&op, 0, sizeof(op));

	printf("Attempt to issue transactions from %d child account...\n", account_id);
	// Defining the parameter value sent to TA, the parameter are
	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_OUTPUT, TEEC_VALUE_INPUT);
	op.params[0].value.a = pin;
	op.params[0].value.b = 0; // 0---unchecked, 1---correct pin, 2---incorrect pin
	op.params[1].tmpref.buffer = get_txbuf_data(buf);
	op.params[1].tmpref.size = get_txbuf_next(buf);
	op.params[2].tmpref.buffer = out;
	op.params[2].tmpref.size = 72;
	op.params[3].value.a = account_id;

	res = TEEC_InvokeCommand(&sess, cmd_id, &op, &err_origin);
	if (res != TEEC_SUCCESS) {
		ERR_MSG("TEEC_InvokeCommand failed with code 0x%x origin 0x%x", res, err_origin);
	}
	if (op.params[0].value.b == 2) {
		ERR_MSG("Incorrect pin");
	}

	free_tx(tx);
	free_txbuf(buf);

	printf("Retrieved signed transaction\n");
	for (uint32_t i = 0; i < op.params[2].tmpref.size; i++) {
		printf("%02x", out[i]);
	}
	printf("\n");

	return res;
}


static TEEC_Result ta_bitcoin_cmd_get_bitcoin_address(TEEC_Session sess, uint32_t pin, uint32_t cmd_id, uint32_t err_origin, uint32_t account_id){
	TEEC_Operation op;
	TEEC_Result res;

	// Clear the TEEC_Operation struct, same as clearing parameter type
	memset(&op, 0, sizeof(op));

	printf("Getting bitcoin address...\n");
	// Defining the parameter value sent to TA, the parameter are
	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_VALUE_INPUT, TEEC_MEMREF_TEMP_OUTPUT, TEEC_NONE);
	op.params[0].value.a = pin;
	op.params[0].value.b = 0; // 0---unchecked, 1---correct pin, 2---incorrect pin
	op.params[1].value.a = account_id;
	op.params[2].tmpref.buffer = malloc(25);
	op.params[2].tmpref.size = 25;

	res = TEEC_InvokeCommand(&sess, cmd_id, &op, &err_origin);
	if (res != TEEC_SUCCESS) {
		ERR_MSG("TEEC_InvokeCommand failed with code 0x%x origin 0x%x", res, err_origin);
	}
	if (op.params[0].value.b == 2) {
		ERR_MSG("Incorrect pin");
	}


	print_uint8(op.params[2].tmpref.buffer,25);
	return TEEC_SUCCESS;
}



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  // MX_GPIO_Init();
  MX_USART1_UART_Init();
  // MX_RNG_Init();
  /* USER CODE BEGIN 2 */

  // Set the random number generator
  // rng_init();

  // Variables used by the TEE Client API
  TEEC_Result res;
  TEEC_Context ctx = {0};
  TEEC_Session sess = {0};
  TEEC_UUID uuid = TA_BITCOIN_WALLET_UUID;

  uint32_t err_origin;
  //uint32_t cmd_id;
  uint32_t pin;
  uint32_t account_id = 0;
  char mnemonic[MNEMONIC_LENGTH] = "Hello world from Trento!";

  // NOTE: parameters are hardcoded as it is a demo and input from the user in the Baremetal TEE is out of scope
  
  // Parameters input and validation should be done in a real-world application
  // other param validation
  /*if(check_params(argc, argv) == -1){
	  help();
	  return -1;
  }

  // command validation
  cmd_id = argv[1][0]-'0';

  // pin validation
  if(strlen(argv[2])!=4){
	  printf("bitcoin_wallet: Incorrect pin.\n");
	  return -1;
  }

  // command validation
  cmd_id = argv[1][0]-'0';

  // pin validation
  if(strlen(argv[2])!=4){
	  printf("bitcoin_wallet: Incorrect pin.\n");
	  return -1;
  }
  // mnemonic validation
  if(cmd_id==3){
	  char* temp = mnemonic;
	  const char space = ' ';
	  int i;
	  for(i=4;i<argc;i++){
		  strncpy(temp, argv[i], strlen(argv[i]));
		  temp += strlen(argv[i]);
		  if(i!=(argc-1)){
			  strncpy(temp, &space, 1);
			  temp += 1;
		  }
	  }
  }

  if(cmd_id==5 || cmd_id==6){
	  account_id = argv[4][0]-'0';
  }

  // convert string pin to integer
  pin = (argv[2][0]-'0')*1000 + (argv[2][1]-'0')*100 + (argv[2][2]-'0')*10 +(argv[2][3]-'0'); */

  pin = 1234;

  // Initiliaze context
  res = TEEC_InitializeContext(NULL, &ctx);
  if (res != TEEC_SUCCESS) {
	  ERR_MSG("TEEC_InitializeContext failed with code 0x%x\r\n", res);
  	goto error;
  }

  // Open session with TA
  res = TEEC_OpenSession(&ctx, &sess, &uuid, TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
  if (res != TEEC_SUCCESS) {
	  ERR_MSG("TEEC_Opensession failed with code 0x%x origin 0x%x\r\n", res, err_origin);
	  goto error;
  }

  // Execute the sequence of commands that are invoking the TA functions
  for(int i=0; i<COMMAND_IDS_LEN; i++)
  {
	  int command = command_ids[i];
    switch(command){
      case TA_BITCOIN_WALLET_CMD_1: // Check master key
        ta_bitcoin_cmd_check_masterkey(sess, pin, 1, err_origin);
        break;
      case TA_BITCOIN_WALLET_CMD_2: // Generate new master key
        ta_bitcoin_cmd_generate_new_masterkey(sess, pin, 2, err_origin, mnemonic);
        break;
      case TA_BITCOIN_WALLET_CMD_3: // Mnemonic to master key
        ta_bitcoin_cmd_mnemonic_to_masterkey(sess, pin, 3, err_origin, mnemonic);
        break;
      case TA_BITCOIN_WALLET_CMD_4: // Erase master key
        ta_bitcoin_cmd_erase_masterkey(sess, pin, 4, err_origin);
        break;
      case TA_BITCOIN_WALLET_CMD_5: // Issue transactions
        ta_bitcoin_cmd_issue_transactions(sess, pin, 5, err_origin, account_id);
        break;
      case TA_BITCOIN_WALLET_CMD_6: // Get bitcoin address
    	  ta_bitcoin_cmd_get_bitcoin_address(sess,pin, 6, err_origin, account_id);
        break;
      default:
        goto error;
    }
  }

  // Close session
  TEEC_CloseSession(&sess);

  // Finalize context
  TEEC_FinalizeContext(&ctx);

  // Deinit RNG
  // rng_deinit();

  goto exit;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
error:
  while (1)
  {
    /* USER CODE END WHILE */
	 ERR_MSG("Error during the execution of Bitcoin Wallet client\r\n");
	 HAL_GPIO_TogglePin(LED3_WIFI__LED4_BLE_GPIO_Port, LED3_WIFI__LED4_BLE_Pin);
	 HAL_Delay(1000);
    /* USER CODE BEGIN 3 */
  }

exit:
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */

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
	  Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
	  /* Initialization Error */
	  Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_RNG;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLLSAI1;
  PeriphClkInit.RngClockSelection = RCC_RNGCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 24;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_48M2CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, M24SR64_Y_RF_DISABLE_Pin|M24SR64_Y_GPO_Pin|ISM43362_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ARD_D10_Pin|SPBTLE_RF_RST_Pin|ARD_D9_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ARD_D8_Pin|ISM43362_BOOT0_Pin|ISM43362_WAKEUP_Pin|LED2_Pin
                          |SPSGRF_915_SDN_Pin|ARD_D5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, USB_OTG_FS_PWR_EN_Pin|PMOD_RESET_Pin|STSAFE_A100_RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPBTLE_RF_SPI3_CSN_GPIO_Port, SPBTLE_RF_SPI3_CSN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, VL53L0X_XSHUT_Pin|LED3_WIFI__LED4_BLE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPSGRF_915_SPI3_CSN_GPIO_Port, SPSGRF_915_SPI3_CSN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ISM43362_SPI3_CSN_GPIO_Port, ISM43362_SPI3_CSN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : M24SR64_Y_RF_DISABLE_Pin M24SR64_Y_GPO_Pin ISM43362_RST_Pin ISM43362_SPI3_CSN_Pin */
  GPIO_InitStruct.Pin = M24SR64_Y_RF_DISABLE_Pin|M24SR64_Y_GPO_Pin|ISM43362_RST_Pin|ISM43362_SPI3_CSN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_OTG_FS_OVRCR_EXTI3_Pin SPSGRF_915_GPIO3_EXTI5_Pin SPBTLE_RF_IRQ_EXTI6_Pin ISM43362_DRDY_EXTI1_Pin */
  GPIO_InitStruct.Pin = USB_OTG_FS_OVRCR_EXTI3_Pin|SPSGRF_915_GPIO3_EXTI5_Pin|SPBTLE_RF_IRQ_EXTI6_Pin|ISM43362_DRDY_EXTI1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_EXTI13_Pin */
  GPIO_InitStruct.Pin = BUTTON_EXTI13_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_EXTI13_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ARD_A5_Pin ARD_A4_Pin ARD_A3_Pin ARD_A2_Pin
                           ARD_A1_Pin ARD_A0_Pin */
  GPIO_InitStruct.Pin = ARD_A5_Pin|ARD_A4_Pin|ARD_A3_Pin|ARD_A2_Pin
                          |ARD_A1_Pin|ARD_A0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : ARD_D1_Pin ARD_D0_Pin */
  GPIO_InitStruct.Pin = ARD_D1_Pin|ARD_D0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ARD_D10_Pin SPBTLE_RF_RST_Pin ARD_D9_Pin */
  GPIO_InitStruct.Pin = ARD_D10_Pin|SPBTLE_RF_RST_Pin|ARD_D9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : ARD_D4_Pin */
  GPIO_InitStruct.Pin = ARD_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
  HAL_GPIO_Init(ARD_D4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ARD_D7_Pin */
  GPIO_InitStruct.Pin = ARD_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ARD_D7_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ARD_D13_Pin ARD_D12_Pin ARD_D11_Pin */
  GPIO_InitStruct.Pin = ARD_D13_Pin|ARD_D12_Pin|ARD_D11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : ARD_D3_Pin */
  GPIO_InitStruct.Pin = ARD_D3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ARD_D3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ARD_D6_Pin */
  GPIO_InitStruct.Pin = ARD_D6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ARD_D6_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ARD_D8_Pin ISM43362_BOOT0_Pin ISM43362_WAKEUP_Pin LED2_Pin
                           SPSGRF_915_SDN_Pin ARD_D5_Pin SPSGRF_915_SPI3_CSN_Pin */
  GPIO_InitStruct.Pin = ARD_D8_Pin|ISM43362_BOOT0_Pin|ISM43362_WAKEUP_Pin|LED2_Pin
                          |SPSGRF_915_SDN_Pin|ARD_D5_Pin|SPSGRF_915_SPI3_CSN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LPS22HB_INT_DRDY_EXTI0_Pin LSM6DSL_INT1_EXTI11_Pin ARD_D2_Pin HTS221_DRDY_EXTI15_Pin
                           PMOD_IRQ_EXTI12_Pin */
  GPIO_InitStruct.Pin = LPS22HB_INT_DRDY_EXTI0_Pin|LSM6DSL_INT1_EXTI11_Pin|ARD_D2_Pin|HTS221_DRDY_EXTI15_Pin
                          |PMOD_IRQ_EXTI12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_OTG_FS_PWR_EN_Pin SPBTLE_RF_SPI3_CSN_Pin PMOD_RESET_Pin STSAFE_A100_RESET_Pin */
  GPIO_InitStruct.Pin = USB_OTG_FS_PWR_EN_Pin|SPBTLE_RF_SPI3_CSN_Pin|PMOD_RESET_Pin|STSAFE_A100_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : VL53L0X_XSHUT_Pin LED3_WIFI__LED4_BLE_Pin */
  GPIO_InitStruct.Pin = VL53L0X_XSHUT_Pin|LED3_WIFI__LED4_BLE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : VL53L0X_GPIO1_EXTI7_Pin LSM3MDL_DRDY_EXTI8_Pin */
  GPIO_InitStruct.Pin = VL53L0X_GPIO1_EXTI7_Pin|LSM3MDL_DRDY_EXTI8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PMOD_SPI2_SCK_Pin */
  GPIO_InitStruct.Pin = PMOD_SPI2_SCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PMOD_SPI2_SCK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PMOD_UART2_CTS_Pin PMOD_UART2_RTS_Pin PMOD_UART2_TX_Pin PMOD_UART2_RX_Pin */
  GPIO_InitStruct.Pin = PMOD_UART2_CTS_Pin|PMOD_UART2_RTS_Pin|PMOD_UART2_TX_Pin|PMOD_UART2_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : ARD_D15_Pin ARD_D14_Pin */
  GPIO_InitStruct.Pin = ARD_D15_Pin|ARD_D14_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
