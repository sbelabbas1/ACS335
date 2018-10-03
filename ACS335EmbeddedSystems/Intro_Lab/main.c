#include "stm32f4xx.h"
int main(void) {
	uint32_t ii;
	// Initialize GPIO Port for LEDs
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable GPIOD clock 
	GPIOD->MODER |= GPIO_MODER_MODE13_0; // Set Pin 13 to output mode 
	for(;;){
	GPIOD->BSRR = 1<<13; // Turn on the orange LED
	for(ii=0;ii<26000000;ii++){}
	GPIOD->BSRR = 1<<(13+16); // Turn off the orange LED
	for(ii=0;ii<26000000;ii++){}
	}
};