#include "app.hpp"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>

uint32_t press_count = 0;

extern "C" void app_c(void)
{
	app();
}

class TEST
{
public:
	void toggle_print();
};

void app(void)
{
	TEST blink;
	while (1)
	{
		blink.toggle_print();
		HAL_Delay(100);
	}
}

void TEST::toggle_print()
{
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	static uint32_t i = 0;
	printf("N: %ld, Buttion count: %ld.\r\n", i++, press_count);
}

extern "C" int _write(int file, char *ptr, int len)
{
	(void)file; // hack for fix warning - unused int file.
	HAL_UART_Transmit(&hlpuart1, (uint8_t *)ptr, len, 1000);
	return len;
}

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_13)
		press_count++;
}