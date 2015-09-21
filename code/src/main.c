#include <math.h>

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h"
#include "lcd.h"

#define PI 3.14159265358979323846
#define BUF_SIZE 512

volatile uint32_t gDelayMS;
volatile uint32_t gICVal1Buf[BUF_SIZE];
volatile uint32_t gICVal2Buf[BUF_SIZE];
volatile uint32_t gFBI;
volatile uint16_t gCaptureIndex = 0;
volatile uint8_t gCapturing;

const double_t c_osc = 0.0000005;
const double_t l_osc = 0.00001;

TIM_HandleTypeDef gTimHandle;

void SystemClock_Config(void);
void delay(uint32_t delay);

int main(void)
{
	GPIO_InitTypeDef gpioInit;
	TIM_IC_InitTypeDef timIcInit;
	double_t ind;
	uint32_t freq, tempFreq, clock, i;

	HAL_Init();
	SystemClock_Config();

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_RCC_TIM15_CLK_ENABLE();

	if (SysTick_Config(SystemCoreClock / 1000)) {
		while (1);
	}

	gpioInit.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
	gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInit.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOA, &gpioInit);
	gpioInit.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
	HAL_GPIO_Init(GPIOC, &gpioInit);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_RESET);

	gpioInit.Pin = GPIO_PIN_14;
	gpioInit.Mode = GPIO_MODE_INPUT;
	gpioInit.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &gpioInit);

	__HAL_AFIO_REMAP_TIM15_ENABLE();

	HAL_NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);

	gTimHandle.Instance = TIM15;
	gTimHandle.Init.Prescaler = 0;
	gTimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	gTimHandle.Init.Period = 0xFFFF;
	gTimHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	gTimHandle.Init.RepetitionCounter = 0;

	timIcInit.ICPolarity = TIM_ICPOLARITY_RISING;
	timIcInit.ICSelection = TIM_ICSELECTION_DIRECTTI;
	timIcInit.ICPrescaler = TIM_ICPSC_DIV8;
	timIcInit.ICFilter = 0xB;

	HAL_TIM_IC_Init(&gTimHandle);
	HAL_TIM_IC_ConfigChannel(&gTimHandle, &timIcInit, TIM_CHANNEL_1);

	gCapturing = 1;

	HAL_TIM_IC_Start_IT(&gTimHandle, TIM_CHANNEL_1);

	lcd_init();

	clock = HAL_RCC_GetPCLK2Freq();

	while (1) {
		while (gCapturing);

		freq = 0;
		for (i = 0; i < BUF_SIZE; i++) {
			if (gICVal2Buf[i] > gICVal1Buf[i]) {
				tempFreq = clock / (gICVal2Buf[i] - gICVal1Buf[i]);
			} else if (gICVal2Buf[i] < gICVal1Buf[i]) {
				tempFreq = clock / ((0xFFFF - gICVal1Buf[i]) + gICVal2Buf[i]);
			} else {
				tempFreq = 0;
			}
			freq += (tempFreq * 8);
		}
		freq /= BUF_SIZE;
		ind = (pow((1 / (2 * PI * freq)), 2));
		ind /= c_osc;
		ind -= l_osc;
		lcd_clear();
		lcd_write_string("L: ");
		if (ind < 0.000001) {
			lcd_write_number(roundf(ind * 1000000000));
			lcd_write_string("nH");
		} else if (ind < 0.001 && ind >= 0.000001) {
			lcd_write_number(roundf(ind * 1000000));
			lcd_write_string("uH");
		} else if (ind >= 0.001) {
			lcd_write_number(roundf(ind * 1000));
			lcd_write_string("mH");
		}
		lcd_set_line(1);
		lcd_write_string("Freq:");
		lcd_write_number(freq);
		lcd_write_string(" Hz");
		delay(500);

		gFBI = 0;
		gCapturing = 1;
		HAL_TIM_ReadCapturedValue(&gTimHandle, TIM_CHANNEL_1);
		HAL_TIM_IC_Start_IT(&gTimHandle, TIM_CHANNEL_1);
	}
}

void delay(uint32_t delay)
{
	gDelayMS = delay;
	while (gDelayMS != 0);
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 24000000
 *            HCLK(Hz)                       = 24000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 1
 *            APB2 Prescaler                 = 1
 *            HSE Frequency(Hz)              = 8000000
 *            HSE PREDIV1                    = 2
 *            PLLMUL                         = 6
 *            Flash Latency(WS)              = 0
 * @param  None
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef clkinitstruct = {0};
	RCC_OscInitTypeDef oscinitstruct = {0};

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
	oscinitstruct.HSEState        = RCC_HSE_ON;
	oscinitstruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV2;
	oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
	oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
	oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL6;
	if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK) {
		/* Initialization Error */
		while(1);
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	clocks dividers */
	clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
	clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_0)!= HAL_OK) {
		/* Initialization Error */
		while(1);
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
		if (gCaptureIndex == 0) {
			gICVal1Buf[gFBI] = HAL_TIM_ReadCapturedValue(&gTimHandle, TIM_CHANNEL_1);
			gCaptureIndex = 1;
		} else if (gCaptureIndex == 1) {
			gICVal2Buf[gFBI++] = HAL_TIM_ReadCapturedValue(&gTimHandle, TIM_CHANNEL_1);
			gCaptureIndex = 0;
			if (gFBI == BUF_SIZE) {
				gCapturing = 0;
				HAL_TIM_IC_Stop_IT(&gTimHandle, TIM_CHANNEL_1);
			}
		}
	}
}

void TIM1_BRK_TIM15_IRQHandler(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_TIM_IRQHandler(&gTimHandle);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
}

void SysTick_Handler(void)
{
	if (gDelayMS > 0) {
		gDelayMS--;
	}
}
