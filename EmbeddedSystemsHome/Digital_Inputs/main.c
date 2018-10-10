#include "stm32f4xx.h"

int main(void){
	//Initiate GPIOD and GREEN LED
	RCC->AHB1ENR |=	0X000008;
	GPIOD->MODER |= GPIO_MODER_MODER12_0; 	
	
};