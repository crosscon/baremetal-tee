#include "reflash.h"

#define LAST_BANK1_PAGE 255	// page number of last page of flash bank 1 as described in STM32L475 manual

extern uint32_t g_pfnVectors;

void SystemClock_Config(void);
void SysTick_Handler(void);

/**
 * @brief Erase all pages within memory range specified regardless of banks
 * @param address: first memory location to erase
 * @param len: amount of bytes to erase
 */
void erase(uint32_t address, uint32_t len) {
	uint32_t first_page_s = (uint32_t) address & ~(2047);				// calculate start address of first page erased
	uint32_t last_page_s = ((uint32_t) address + len - 1) & ~(2047);	// calculate start address of last page erased

	uint32_t s_page = (first_page_s - FLASH_BASE) / FLASH_PAGE_SIZE;	// calculate number of first page erased
	uint32_t e_page = (last_page_s - FLASH_BASE) / FLASH_PAGE_SIZE;		// calculate number of last page erased

	// TODO test this whole code

	uint32_t bank1_pages = 0;
	uint32_t bank1_s_page, bank1_e_page;
	if(s_page <= LAST_BANK1_PAGE) {
		bank1_s_page = s_page;
		bank1_e_page = e_page <= LAST_BANK1_PAGE ? e_page : LAST_BANK1_PAGE;
		bank1_pages = bank1_e_page - bank1_s_page + 1;
	}

	uint32_t bank2_pages = 0;
	uint32_t bank2_s_page, bank2_e_page;
	if(e_page > LAST_BANK1_PAGE) {
		bank2_s_page = s_page > LAST_BANK1_PAGE ? s_page : LAST_BANK1_PAGE + 1;
		bank2_e_page = e_page;
		bank2_pages = bank2_e_page - bank2_s_page + 1;
	}

	uint32_t erase_error;

	if(bank1_pages) {
		FLASH_EraseInitTypeDef bank1_erase_confige = {
			FLASH_TYPEERASE_PAGES,
			1,	// bank 1
			bank1_s_page,
			bank1_pages
		};
		HAL_FLASHEx_Erase(&bank1_erase_confige, &erase_error);
	}

	if(bank2_pages) {
		FLASH_EraseInitTypeDef bank2_erase_confige = {
			FLASH_TYPEERASE_PAGES,
			2,	// bank 2
			bank2_s_page,
			bank2_pages
		};
		HAL_FLASHEx_Erase(&bank2_erase_confige, &erase_error);
	}
}

/**
 * @brief Performs a "move" between two flash memory location
 * @param src: address where source data is located
 * @param dst: address where data is moved to
 * @param len: amout of bytes to move
 */
void reflash(uint32_t* src, uint32_t* dst, uint32_t len) {
	/* Setup in-RAM Vector Table */
	SCB->VTOR = (uint32_t) &g_pfnVectors;

	HAL_Init();
	SystemClock_Config();

	/* Unlock Flash */
	HAL_FLASH_Unlock();
	/* Clear flash PG flag (might be set due to previous use) */
	CLEAR_BIT(FLASH->CR, FLASH_CR_PG);

	/* Erase destination flash memory */
	erase((uint32_t) dst, len);

	/* Transfer content from src to dst */
	uint32_t* curr = src;
	while((uint32_t) curr < ((uint32_t) src + len)) {
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t) dst, *((uint64_t *) curr));
		dst += 2;	// advance destination pointer by double word (64 bits)
		curr += 2;	// advance source pointer by double word (64 bits)
	}

	/* Erase content from src to prevent information leak */
	erase((uint32_t) src, len);

	/* Lock Flash */
	HAL_FLASH_Lock();

	/* Reboot board */
	HAL_NVIC_SystemReset();
}

void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = 0;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}

void SysTick_Handler(void) {
  HAL_IncTick();
}
