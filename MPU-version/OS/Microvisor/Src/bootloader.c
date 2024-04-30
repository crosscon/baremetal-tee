#include "bootloader.h"
#include "memory_map.h"
#include "virtual_IPSR.h"
#include "stm32l475vg_mpu.h"
#include "activator.h"
#include "it.h"
#include "wifi.h"
#include "microvisor_config.h"
#include "sec_comm.h"
#include "wifi_wrapper.h"
#include "ota.h"
#include "permanent_storage.h"
#include "mbedtls_rng_wrapper.h"
/* mbedtls library headers */
#include "mbedtls/pk.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/entropy.h"

/*
* bootloader file:
* primary code unit of microvisor, is immediately called by Reset_Handler after board reboot.
* Performs all necessary tasks (activation check, error reporting, update checking) 
* before transitioning to fortified application execution.
*/


/**
 * Disables privileges for code running in thread mode and begins executing
 * the user app.
 * Given the fact that the MPU is configured in order to allow the execution
 * of Microvisor code only when privileges are available, the following function
 * must be stored in a separate memory area where the MPU policies are different
 * and the execution of the code is allowed even in the absence of privileges.
 */
__attribute__((section(".microvisor-nopri"))) static void start_app(unsigned int sp, unsigned int pc) {
	__asm__(
		/* Disable Thread mode privileges */
		"mrs r3, CONTROL\n"
		"orr r3, #1\n"
		"msr CONTROL, r3\n"
		"dsb\n"
		"isb\n"
		
		/* Bootstrap user app */
		"msr msp, r0\n"	// load SP
		"bx r1\n"		// jump to application Reset_Handler
	);
}

/**
 * Set CCR.NONBASETHRDENA to 1 in order to disable the integrity check on exception return.
 * This is done to prevent the ARMv7 architecture from interfearing with the process
 * of interrupt deprioritization in the event of 2 interrupts (A and B with B having
 * higher priority than A) where interrupt B could preempt the execution of A during
 * the exception catching routine immediately before interrupts are disabled.
 */
void Disable_Exception_Integrity_Check() {
	__asm__(
		"ldr r0, =0xE000ED14\n"	// address of Configuration and Control Register (CCR)
		"ldr r1, [r0]\n"
		"orr r1, #1\n"
		"str r1, [r0]\n"
	);
}

/**
 * Clears Data and BSS segments from RAM in order to prevent
 * recovery of sensitive infomration from user application.
 */
void Clear_Data_BSS() {
	// start and end variable for both Data and BSS segments
	extern unsigned int _sdata;
	extern unsigned int _edata;
	extern unsigned int _sbss;
	extern unsigned int _ebss;

	uint32_t* ptr;
	// Iterate through the segments and set all values to 0
	/* Zero-fill Data */
	for(ptr = (uint32_t *) &_sdata; ptr < (uint32_t *) &_edata; ptr++) {
		*ptr = 0;
	}
	/* Zero-fill BSS */
	for(ptr = (uint32_t *) &_sbss; ptr < (uint32_t *) &_ebss; ptr++) {
		*ptr = 0;
	}
}

/**
 * Standard configuration of the system clock for the STM32L4xx family
*/
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
 * Customized boot function for the board.
 * 
 * Steps: 
 * - Performs all standard necessary tasks (HAL_Init, SystemClock_Config)
 * - Initializes the Wifi module
 * - Connects to the Wifi network
 * - If the board is not activated, performs the activation process by:
 *  	- creating a secure communication channel with the Activation Server
 * 		- exchanging the symmetric encryption key with the Activation Server
 * 		- shares the board UUID with the Activation Server
 * 		- receives the activation ACK from the Activation Server
 * - If the board is activated, performs the update process by:
 * 		- reporting errors to the Update Server
 * 		- updating the microvisor if necessary
 * 		- updating the user application if necessary 
 * - Transition to vector table with interrupt deprioritization
 * - Configures the MPU based on the custom map
 * - Initializes the Virtual IPSR
 * - Clears Data and BSS segments from RAM
 * - Set the SP and PC for the fortified application and starts it
*/
void boot(void) {
	/* sec_comm layer data structures */
	sec_comm_context ctx;

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize Wifi module */
	if(WIFI_Init() ==  WIFI_STATUS_OK) {
		/* Connect to Wifi network */
		if( WIFI_Connect(SSID, PASSWORD, WIFI_ECN_WPA2_PSK) == WIFI_STATUS_OK) {
			if(!activator_is_board_activated()) {
				/* Activate board and perform first boot initialization operations */
				/* Wipe permanent storage */
				if(perma_storage_wipe() != PERMA_STORAGE_OK)
					soft_reset();	//	Initialization error
				/* Recompute fortified application size (if present) */
				perma_storage_set_firmware_size(ota_compute_firmware_size());				
				/* Initialize sec_comm layer */
				if(SEC_COMM_OK != sec_comm_init(&ctx, 0))
					goto activation_over;
				
				/* Start the connection */
				if(SEC_COMM_OK != sec_comm_connect(&ctx, Activation_Server_IP, ACTIVATION_SERVER_PORT, LOCAL_PORT))
					goto activation_over;
				
				/* Create symmetric encryption key */
				if(HAL_OK != mbedtls_rng_init())	// initialize rng wrapper
					goto activation_over;
				uint8_t key[KEY_LEN];
				uint32_t olen;
				if(0 != mbedtls_rng_f_source(NULL, key, KEY_LEN, (size_t *) &olen))
					goto activation_over;	// key generation failed
				if(olen != KEY_LEN)
					goto activation_over;	// key generation failed

				/* Initialize mbedtls data structures */
				mbedtls_pk_context pk_ctx;
				mbedtls_ctr_drbg_context ctr_drbg_ctx;
				mbedtls_entropy_context entropy_ctx;
				mbedtls_pk_init(&pk_ctx);
				mbedtls_ctr_drbg_init(&ctr_drbg_ctx);
				mbedtls_entropy_init(&entropy_ctx);

				/* Configure drbg and entropy layers */
				if(0 != mbedtls_entropy_add_source(&entropy_ctx, mbedtls_rng_f_source, NULL, 1, MBEDTLS_ENTROPY_SOURCE_STRONG))
					goto activation_over;	// configuration failed
				if(0 != mbedtls_ctr_drbg_seed(&ctr_drbg_ctx, mbedtls_entropy_func, &entropy_ctx, (const unsigned char *) STM32L4XX_UID, STM32L4XX_UID_LEN))
					goto activation_over;	// seeding failed
				
				/* Parse Activation Server public key */
				if(0 != mbedtls_pk_parse_public_key(&pk_ctx, Activation_Server_PubKey, ACTIVATION_SERVER_PUBKEY_LEN))
					goto activation_over;	// key parsing failed
				
				/* Encrypt symmetric key with Activation Server public key */
				uint8_t encrypted_key[256];
				uint32_t encrypted_key_len;
				if(0 != mbedtls_pk_encrypt(&pk_ctx, key, KEY_LEN, encrypted_key, (size_t *) &encrypted_key_len, 256, mbedtls_ctr_drbg_random, &ctr_drbg_ctx))
					goto activation_over;	// encryption failed
				if(encrypted_key_len != 256)
					goto activation_over;	// length of encrypted key does not match
				
				/* Send encrypted key length */
				if(WIFI_STATUS_OK != wifi_wrapper_send_data(ctx.socket, (uint8_t *) &encrypted_key_len, 4))
					goto activation_over;
				/* Send encrypted key */
				if(WIFI_STATUS_OK != wifi_wrapper_send_data(ctx.socket, encrypted_key, encrypted_key_len))
					goto activation_over;
				/* Read Activation Server ACK */
				int32_t ack;
				if(WIFI_STATUS_OK != wifi_wrapper_receive_data(ctx.socket, (uint8_t *) &ack, 4))
					goto activation_over;
				if(ack != 1)
					goto activation_over;
				
				/* Set sec_comm encryption key */
				if(SEC_COMM_OK != sec_comm_set_key(&ctx, key))
					goto activation_over;	// setting symmetric encryption key failed
				
				/* Attempt to activate board */
				if(activator_activate_board(&ctx) == ACTIVATOR_COMMUNICATION_ERROR)
					goto activation_over;
				
				/* Free resources */
				activation_over:
				mbedtls_rng_deinit();
				sec_comm_disconnect(&ctx);
				sec_comm_deinit(&ctx);
			}

			/* Exchange information with Update Server if necessary */
			/* [Re]Initialize sec_comm layer */
			if(SEC_COMM_OK != sec_comm_init(&ctx, 0))
					goto update_over;
			/* Set symmetric encryption key */
			if(SEC_COMM_OK != sec_comm_set_key(&ctx, Update_Server_Key))
					goto update_over;
			
			/* Start the connection */
			if(SEC_COMM_OK != sec_comm_connect(&ctx, Update_Server_IP, UPDATE_SERVER_PORT, LOCAL_PORT))
					goto update_over;

			/* Identify to server */
			if(WIFI_STATUS_OK != wifi_wrapper_send_data(ctx.socket, (uint8_t *) STM32L4XX_UID, STM32L4XX_UID_LEN))	// send board UUID in clear
				goto update_over;
			int32_t identification;
			if(WIFI_STATUS_OK != wifi_wrapper_receive_data(ctx.socket, (uint8_t *) &identification, 4))	// read identification result
				goto update_over;
			if(identification != 1)
				goto update_over;

			/* Report errors if necessary */
			if(OTA_OK != ota_report_error(&ctx))
				goto update_over;

			/* Perform microvisor update if necessary */
			if(OTA_OK != ota_update_microvisor(&ctx))
				goto update_over;

			/* Perform user application update if necessary */
			if(OTA_UPDATE_FAIL == ota_update_firmware(&ctx))
				soft_reset();	// update failed, reset board

			/* Free resources */
			update_over:
			sec_comm_disconnect(&ctx);
			sec_comm_deinit(&ctx);
		}
	}
	/* Communication part over, transition to user application */

	/* Verify board activation before transitioning */
	if(!activator_is_board_activated())
		soft_reset();

	/* Disable used interrupts */
	HAL_NVIC_DisableIRQ(EXTI1_IRQn);
	HAL_NVIC_DisableIRQ(SPI3_IRQn);
	/* Disable SysTick */
	SysTick->CTRL &= 0xfffffffe;

	/* Transition to vector table with interrupt deprioritization */
	SCB->VTOR = (uint32_t) &__isr_vector_deprio_start__;

	Configure_MPU();
	Disable_Exception_Integrity_Check();
	Initialize_Virtual_IPSR();

	unsigned int* app_vector_table = &__flash_start__;
	unsigned int app_sp = app_vector_table[0];
	unsigned int app_entry = app_vector_table[1];

	Clear_Data_BSS();
	start_app(app_sp, app_entry);
}

/**
 * Reset function for the board
*/
void soft_reset() {
	__asm__(
		"bkpt\n"
	);
	HAL_NVIC_SystemReset();
}

/**
	* @brief  EXTI line detection callback.
	* @param  GPIO_Pin: Specifies the port pin connected to corresponding EXTI line.
	* @retval None
	*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
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