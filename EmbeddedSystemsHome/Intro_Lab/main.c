#include "stm32f4xx.h";
int main(void){;
	uint32_t ii;
	// Initialize GPIO Port for LEDs
	// RCC->AHB1ENR |= 1<<3; //Enable GPIOD clock using direct bit placement 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable GPIOD clock using predefined definition 
	// GPIOD->MODER |= 1<<24; 					// Activate GPIOD Port 12 using direct bit placement 
	GPIOD->MODER |= GPIO_MODER_MODE12_0; // Activate GPIOD Port 12 using predefined position definition 
	GPIOD->MODER |= GPIO_MODER_MODE13_0; // Activate GPIOD Port 13 using predefined position definition 
	GPIOD->MODER |= GPIO_MODER_MODE14_0; // Activate GPIOD Port 14 using predefined position definition 
	GPIOD->MODER |= GPIO_MODER_MODE15_0; // Activate GPIOD Port 15 using predefined position definition 
	for(;;){
		GPIOD->BSRR = 1<<13; 	//Set pin 12 on for ORANGE LED
		GPIOD->BSRR = 1<<30;	// Set pin 13 off gor RED LED
		GPIOD->BSRR = 1<<28;	// Set pin 12 off for GREEN LED
		GPIOD->BSRR = 1<<15; 	//Set pin 12 on for BLUE LED
		for(ii=0; ii<26000000; ii++){} // One second delay
		GPIOD->BSRR = 1<<29;	// Set pin 13 off gor ORANGE LED
		GPIOD->BSRR = 1<<14; 	//Set pin 12 on for RED LED
		GPIOD->BSRR = 1<<12;	//Set pin 12 on for GREEN LED	
		GPIOD->BSRR = 1<<31;	// Set pin 13 off gor BLUE LED
		for(ii=0; ii<26000000; ii++){} // One second delay
	}
}