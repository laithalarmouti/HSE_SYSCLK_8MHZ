#include "stm32f4xx_hal.h"
#include "main.h"
#include <string.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0









//PRIVATE FUNCTION DEFINITIONS

void UART2_Init();
void Error_Handler();





UART_HandleTypeDef huart2;





int main(void)
{
	char msg[100];
	RCC_OscInitTypeDef osic_init;
	RCC_ClkInitTypeDef clk_init;
	HAL_Init();


	memset(&osic_init,0,sizeof(osic_init));
	osic_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osic_init.HSEState = RCC_HSE_BYPASS;
	if(HAL_RCC_OscConfig(&osic_init) != HAL_OK)
	{
		Error_Handler();
	}

	memset(&clk_init,0,sizeof(clk_init));
	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2;
	clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
	clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

	if(HAL_RCC_ClockConfig(&clk_init, FLASH_ACR_LATENCY_0WS) != HAL_OK)
	{
		Error_Handler();
	}

	__HAL_RCC_HSI_DISABLE();


	//SYSTICK CONFIG
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	HAL_SYSTICK_Config(HAL_RCC_GetSysClockFreq() / 1000);




	UART2_Init();

	memset(msg,0,sizeof(msg));
	sprintf(msg,"SYSCLK : %ld\r\n",HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	memset(msg,0,sizeof(msg));
	sprintf(msg,"HCLK : %ld\r\n",HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	memset(msg,0,sizeof(msg));
	sprintf(msg,"PCLK1 : %ld\r\n",HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	memset(msg,0,sizeof(msg));
	sprintf(msg,"PCLK2 : %ld\r\n",HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);


	while(1);
	return 0;


}




void Error_Handler()
{
	while(1);
}

void UART2_Init()
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		//ERROR
		Error_Handler();
	}

}


