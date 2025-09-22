#include "bootloader.h"
#include "memory_map.h"
#include "virtual_IPSR.h"
#include "stm32l475vg_mpu.h"
#include "it.h"
#include "wifi.h"
#include "microvisor_config.h"
#include "sec_comm.h"
#include "wifi_wrapper.h"
#include "ota.h"
#include "permanent_storage.h"
#include "mbedtls_rng_wrapper.h"
#include "internal_core_api.h"
/* mbedtls library headers */
#include "mbedtls/pk.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/entropy.h"
#include "flash.h"
#include "tee_common.h"

#include <stdarg.h>
#include <stdio.h>

/*
* bootloader file:
* primary code unit of microvisor, is immediately called by Reset_Handler after board reboot.
* Performs all necessary initialization tasks (UART, MPU, etc.)
* before transitioning to fortified application execution.
*/

// Define the UART handle used to print messages to the console
// This variable is stored in the .TEE_TA_data section of the binary
// that is accessible by both the TEE and the TAs.
UART_HandleTypeDef __attribute__((section(".TEE_TA_data"))) puart;
RNG_HandleTypeDef hrng;

// Define a custom putchar function to put characters on the UART interface
__attribute__((section(".microvisor-nopri"))) int putchar(int ch)
{
	// Wait until the transmit data register is empty
    while (!(USART1->ISR & USART_ISR_TXE));  // Wait for TXE (Transmit Data Register Empty)

    USART1->TDR = ch;  // Send character

    // Optionally wait for transmission to complete (if desired)
    while (!(USART1->ISR & USART_ISR_TC));  // Wait for TC (Transmission Complete)

    return ch;
}

// Define a custom printf function to print messages to the console
// This function is stored in the .microvisor-nopri section of the binary 
// in order to be accessible also by the TAs
// The custom printf function was needed because the standard printf function
// uses internal buffers and data structures that were difficult to control and manage
__attribute__((section(".microvisor-nopri")))  int custom_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    for (const char *ptr = format; *ptr != '\0'; ++ptr) {
        if (*ptr == '%') {
            ++ptr;
            switch (*ptr) {
                case 'd': { // Decimal
                    int num = va_arg(args, int);
                    if (num < 0) {
                        putchar('-');
                        num = -num;
                    }
                    char buffer[10];
                    int i = 0;
                    do {
                        buffer[i++] = (num % 10) + '0';
                        num /= 10;
                    } while (num);
                    while (i > 0) {
                        putchar(buffer[--i]);
                    }
                    break;
                }
                case 'x': { // Hexadecimal
                    unsigned int num = va_arg(args, unsigned int);
                    putchar('0');
                    putchar('x');
                    for (int i = (sizeof(unsigned int) * 2) - 1; i >= 0; --i) {
                        int nibble = (num >> (i * 4)) & 0xF;
                        putchar(nibble < 10 ? nibble + '0' : nibble - 10 + 'A');
                    }
                    break;
                }
                case 's': { // String
                    const char *str = va_arg(args, const char*);
                    while (*str) {
                        putchar(*str++);
                    }
                    break;
                }
                case 'c': { // Single character
                    char ch = (char)va_arg(args, int);
                    putchar(ch);
                    break;
                }
                default:
                    putchar('%');
                    putchar(*ptr);
                    break;
            }
        } else {
            putchar(*ptr);  // Print normal character
        }
    }

    va_end(args);
    return 0;
}

// Initialize the UART1 interface
static void UART_Init(void)
{
  puart.Instance = USART1;
  puart.Init.BaudRate = 115200;
  puart.Init.WordLength = UART_WORDLENGTH_8B;
  puart.Init.StopBits = UART_STOPBITS_1;
  puart.Init.Parity = UART_PARITY_NONE;
  puart.Init.Mode = UART_MODE_TX_RX;
  puart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  puart.Init.OverSampling = UART_OVERSAMPLING_16;
  puart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  puart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&puart) != HAL_OK)
  {
	/* Initialization Error */
	while (1);
  }
}

// Initialize the UART1 interface
static void RNG_Init(void)
{
    hrng.Instance = RNG;
    if (HAL_RNG_Init(&hrng) != HAL_OK)
    {
        while (1);
    }
}

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

//Used to initlialize the internal object arrays
//TODO: IT would be nice to use the BSS but I haven't managed yet
static void internal_TEE_ClearObjects(){
	memset(registeredObjects, 0, sizeof(registeredObjects));
	memset(registeredOperations, 0, sizeof(registeredOperations));
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
 * - Transition to vector table with interrupt deprioritization
 * - Configures the MPU based on the custom map
 * - Initializes the Virtual IPSR
 * - Erases the flash memory area dedicated to secure storage of the TAs
 * - Erases and initializes the heap area for the RAM of TAs
 * - Clears Data and BSS segments from RAM
 * - Set the SP and PC for the fortified application and starts it
*/
void boot(void) {
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();
	/* Initialize the UART interface */
	UART_Init();
    RNG_Init();

	/* Disable used interrupts */
	HAL_NVIC_DisableIRQ(EXTI1_IRQn);
	HAL_NVIC_DisableIRQ(SPI3_IRQn);
	/* Disable SysTick */
	SysTick->CTRL &= 0xfffffffe;

	/* Transition to vector table with interrupt deprioritization */
	SCB->VTOR = (uint32_t) &__isr_vector_deprio_start__;

	/* Configure MPU in order to execute the CA (Client Application) with only permissions in its dedicated areas */
	Configure_MPU();
	Disable_Exception_Integrity_Check();
	Initialize_Virtual_IPSR();

	// Erase both of the flash memory area dedicated to secure storage (?) of the TAs
	flash_erase(1);
	flash_erase(2);

	// Erase and initialize the heap area for the RAM of TAs
	heap_erase();

	// Clear Data and BSS segments from RAM
	Clear_Data_BSS();

	//Clear internal object arrays
	internal_TEE_ClearObjects();

	// Set the SP and PC for the fortified application 
	unsigned int* app_vector_table = &__flash_start__;
	unsigned int app_sp = app_vector_table[0];
	unsigned int app_entry = app_vector_table[1];

	// Start the fortified application
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
