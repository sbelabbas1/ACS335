#include "stm32f4xx.h";
int main(void){

	/*
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //Activate clock for general purpose IO
	GPIOD->MODER |= GPIO_MODER_MODER12_0; //Activate Modder 12 
	Initialise Timer 
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //Enable timer 2 clock
	TIM2->CR1 |= 0<<4; //Set the control register to upcount mode 
	TIM2->CR1 |= 1<<3; //Set the counter to not repeat
	TIM2->CR1 |= 1; //Enables counter 
	TIM2->PSC |= 8399; //Prescaler value defaults to twice the APB1 which is running at 42MHz - so timer of clock is 84MHz
	TIM2->ARR |= 9999; //Sets the delay on timer 
	TIM2->EGR |= 1; //re initialises the timer
	*/
	
	//Initialise GPIO Port for LEDs
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //Enable GPIOD Clock 
	GPIOD->MODER |= GPIO_MODER_MODER12_0; //GPIOD pin 12 output - green LED
	
	//Initialise Timer 2 
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //Enable timer 2 clock 
	
	TIM2->CR1 &= ~0X00000016; //Sets the counter as an upcounter
	TIM2->CR1 |= 0X00000008; //Turn off repeat - i.e. use one pulse mode
	
	TIM2->PSC = 8399; //Prescaler value - the prescaler clock defaults to twice the APB1 which is running at 42MHz - so the timer clock is 84MHz
	TIM2->EGR = 1; //Re-initialises the timer
	TIM2->ARR = 1000; /*sets the value in the autoreload register*/
	
	for(;;){
		GPIOD->BSRR = 1<<12; //Turn on green LED
		TIM2->CR1 |= 1; //Enables the counter
		while((TIM2->SR&0x0001)!=1){}; //TIM2 to implement a 1 second delay
		TIM2->SR &= ~1; //Resets the flag
		GPIOD->BSRR = 1<<(12+16); // Turn off the green LED
		TIM2->CR1 |= 1; //Enables the counter
		while((TIM2->SR&0x0001)!=1){}; //TIM2 to implement a 1 second delay
		TIM2->SR &= ~1; //Resets the flag
	}
	
};
