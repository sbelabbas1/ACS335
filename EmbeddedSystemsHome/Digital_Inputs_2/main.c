#include "stm32f407xx.h"
int main(void){
	//Initiate Green Led
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;	//Initiate GPIOD clock	
	GPIOD->MODER |= GPIO_MODER_MODE13_0;	//Engages pin 14 for output mode for Orange LED
	GPIOD->MODER |= GPIO_MODER_MODE14_0;	//Engages pin 14 for output mode for Red LED
	GPIOD->MODER |= GPIO_MODER_MODE15_0;	//Engages pin 15 for output mode for Blue LED	
	GPIOD->MODER |= GPIO_MODER_MODE12_0;	//Engages pin 12 for output mode for Green LED
	
	
	//Initiate Counter 
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //Enable clock timer 2
	TIM2->CR1 &= ~0x0016;	//Enables event gereration and count up mode 
	TIM2->CR1 |= 0X0008;	//Enables one pulse mode 
	TIM2->PSC = 8399;	//Set prescaler at 10 kHz
	TIM2->ARR = 200;	//20 milisecond count for debouncing 
	TIM2->EGR = 1;	//Reinitialises the counter 
	
	//Initiate Push Button
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	//Initiate GPIOA clock
	GPIOA->MODER &= ~0x00000003; //Pin 0 to set to input mode 
	
	for(;;){
		if(GPIOA->IDR & 0x0001){
			TIM2->CR1 |= 0x0001;	//Enable timer 	
			while(((TIM2->SR)&0x0001) !=0x0001){}//Delay time for debouncing
				/*if((TIM2->SR) == 0x0001){
				GPIOD->BSRR |= 0x00008000;	//Switch on Blue LED is timer correct
			} */
				
			TIM2->SR &= ~0x0001; //resets timer status
			TIM2->EGR = 1;
			TIM2->ARR = 2500; //Set Count for 1 second 				
				
			if(GPIOA->IDR & 0X0001){ //Debouncer Check
				TIM2->CR1 |= 0x0001; //Enables Timer
				GPIOD->BSRR	|= 0x00002000; 	//Switches Orange LED on 	
				GPIOD->BSRR |= 0x00001000;	//Switches Green LED on
				GPIOD->BSRR	|= 0x40000000;	//Switches Red LED off
				GPIOD->BSRR |= 0x80000000; 	//Switches Blue LED off
				while(((TIM2->SR)&0x0001) != 0x0001){}
				TIM2->SR &= ~0x0001; //resets timer status
				GPIOD->BSRR |= 0x00008000;	//Switches Blue LED on
				GPIOD->BSRR	|= 0x00004000;	//Switches Red LED on
				GPIOD->BSRR |= 0x10000000;	//Switches Green LED off
				GPIOD->BSRR	|= 0x20000000; 	//Switches Orange LED off
				TIM2->CR1 |= 0x0001; //Enables Timer
				while(((TIM2->SR)&0x0001) != 0x0001){}
				TIM2->SR &= ~0x0001;	//resets timer status
				GPIOD->BSRR |= 0x80000000; 	//Switches Blue LED off
				GPIOD->BSRR |= 0x10000000; 	//Switches Green LED off
				GPIOD->BSRR	|= 0x20000000; 	//Switches Orange LED off
				GPIOD->BSRR	|= 0x40000000;	//Switches Red LED off
			}
			
		}
		else{
			GPIOD->BSRR |= 0x80000000;	//Switches Blue LED off
			GPIOD->BSRR |= 0x10000000;	//Switches Green LED off
		}
	}
};