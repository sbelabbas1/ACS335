#include "stm32f407xx.h"
int main(void){
	//Initiate GPIO Ports for LED
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //Engage clock register for GPIOD
	GPIOD->MODER |= GPIO_MODER_MODE12_0; //Engage pin 12 for green LED
	
	//Initiate General Purpose Timers
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //Engage Timer registers
	TIM2->CR1 &= ~0x0016; //Ensures that bit 4,2 and 1 are 0
	TIM2->CR1 |= 0x0008;	//Sets bit 3 to 1
	TIM2->PSC = 8399; //Sets prescaler for 10KHz
	TIM2->ARR = 9999; //Sets the timer delay of 1 second 
	TIM2->EGR = 1; //Re initialises the counter 
	
	for(;;){
		GPIOD->BSRR |= RCC_AHB1ENR_GPIODEN; //0x00001000 Sets green LED on
		
		TIM2->CR1 |= 0x0001;	//Enables timer 
		while((TIM2->SR&0x0001)!= 0x0001){};	//Checks if timer has overflowed 
		TIM2->SR &= ~0x0001;	//Resets flag
			
		GPIOD->BSRR = 0x10000000; //Sets the Green LED off
			
		TIM2->CR1 |= 0x0001;	//Sets timer to overflow
		while((TIM2->SR&0x0001) != 0x0001){};	//Checks if timer has overflowed 
		TIM2->SR &= ~0x0001;
	}
	
};	