#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
//#include "362_GFX.h"
#include "usartf0.h"
#include <math.h>
#include <string.h>
#include "stm32f0xx_adc.h"
#include "adc.h"
#include "SPILCD.h"


void displayHome(void){
	 	lcd_clear(WHITE);

    	char meats[] = "MEATS"; //TL
    	char dairy[] = "DAIRY"; //TR
    	char bread[] = "BREAD"; //BL
    	char battery[] = "BATT."; //BR
    	writeWord(meats, 30, 200);
    	writeWord(dairy, 200, 200);

    	writeWord(bread, 30, 60);
    	writeWord(battery, 200, 60);

    	DrawGrid();
}

void setup_gpiox() {
    //Enable clock to GPIOA
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    //YP PA0
    //XP PA2
    //XM PA1
    //YM PA3

    //Set PA0, PA1, PA2, and PA3 to analog mode
    GPIOA->MODER &= ~(0x3<<(2*0));
    GPIOA->MODER |= (0x3<<(2*0));	//set PA0 to analog

    GPIOA->MODER &= ~(0x3<<(2*1));
    GPIOA->MODER |= (0x1<<(2*1));	//set PA1 to OUTPUT

    GPIOA->MODER &= ~(0x3<<(2*2));
    GPIOA->MODER |= (0x1<<(2*2));	//set PA2 to OUTPUT
	GPIOA->ODR |= (1 << 2);			//turn on GPIO PA2

    GPIOA->MODER &= ~(0x3<<(2*3));
    GPIOA->MODER |= (0x0<<(2*3));	//set PA3 to INPUT (RESET)

}

void setup_gpioy() {
    //Enable clock to GPIOA
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    //YP PA0
    //XP PA2
    //XM PA1
    //YM PA3

    //Set PA0, PA1, PA2, and PA3 to analog mode
    GPIOA->MODER &= ~(0x3<<(2*0));
    GPIOA->MODER |= (0x1<<(2*0));	//set PA0 to OUTPUT
	GPIOA->ODR |= (1 << 0);			//turn on GPIO PA0

    GPIOA->MODER &= ~(0x3<<(2*1));
    GPIOA->MODER |= (0x0<<(2*1));	//set PA1 to INPUT(RESET)

    GPIOA->MODER &= ~(0x3<<(2*2));
    GPIOA->MODER |= (0x3<<(2*2));	//set PA2 to analog

    GPIOA->MODER &= ~(0x3<<(2*3));
    GPIOA->MODER |= (0x1<<(2*3));	//set PA3 to OUTPUT

}




void setup_adc() {
    //Enable clock to ADC unit
//    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
//    RCC->CR2 |= RCC_CR2_HSI14ON;
//    while(!(RCC->CR2 & RCC_CR2_HSI14RDY));
//    ADC1->CR |= ADC_CR_ADEN;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->CR2 |= RCC_CR2_HSI14ON;
	ADC1->CR |= ADC_CR_ADEN;
	while(!(ADC1->ISR & ADC_ISR_ADRDY));
}

int read_adc_channel(unsigned int channel) {
	ADC1->CHSELR = 0;
	ADC1->CHSELR |= 1 << channel;
	while(!(ADC1->ISR & ADC_ISR_ADRDY));
	ADC1->CR |= ADC_CR_ADSTART;
	while(!(ADC1->ISR & ADC_ISR_EOC));
	return ((ADC1->DR));
}

int read_x(){
	GPIOA->PUPDR &= ~(0x3<<(2*0));
	GPIOA->PUPDR &= ~(0x3<<(2*1));
	GPIOA->PUPDR &= ~(0x3<<(2*2));
	GPIOA->PUPDR &= ~(0x3<<(2*3));

	GPIOA->PUPDR |= (0x2<<(2*0)); //PA0 = Y+ PULLED DOWN
	GPIOA->PUPDR |= (0x2<<(2*1)); //PA1 = X- PULLED DOWN
	GPIOA->PUPDR |= (0x2<<(2*2)); //PA2 = X+ PULLED DOWN
	GPIOA->PUPDR |= (0x2<<(2*3)); //PA3 = Y- PULLED DOWN
	GPIOC->OSPEEDR |= 0x3 << 4;	  //PA2 = X+

	return(read_adc_channel(0));
}

int read_y(){
	//clear the pupdr
	GPIOA->PUPDR &= ~(0x3<<(2*0));
	GPIOA->PUPDR &= ~(0x3<<(2*1));
	GPIOA->PUPDR &= ~(0x3<<(2*2));
	GPIOA->PUPDR &= ~(0x3<<(2*3));
	//ouput speed high for PA0
	GPIOC->OSPEEDR |= 0x3 << 0;
	//pull down everything except for PA1
	GPIOA->PUPDR |= (0x2<<(2*0));
	GPIOA->PUPDR |= (0x2<<(2*1));
	GPIOA->PUPDR |= (0x2<<(2*2));
	GPIOA->PUPDR |= (0x2<<(2*3));

	return(read_adc_channel(2));
}
