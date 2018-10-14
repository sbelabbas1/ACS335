#include "stm32f407xx.h"

int main(void){
	
	//Initiate GPIOD and GREEN LED
	RCC->AHB1ENR |=	RCC_AHB1ENR_GPIODEN; 	//Initiate clock for GPIOD Green LED
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 	//Initiate clock for GPIOD Green LED 
	GPIOD->MODER |= GPIO_MODER_MODE12_0; 	//Initiate the GPIOD Green LED into general purpose output mode
	//GPIOA->MODER &= ~GPIO_MODER_MODER0;		//Initiate clock for GPIOA
	GPIOD->MODER &= ~0X00000003; // Resets moder 0 to input mode 
	for(;;){
		if(((GPIOA->IDR) & 0X0001) == 0X0001){ //Read for button if it is pressed
			GPIOD->BSRR = 0x00001000;	//Activate Green LED
		}
		else{
			GPIOD->BSRR = 0x10000000;	//Disable Green LED 
		}
	}
};