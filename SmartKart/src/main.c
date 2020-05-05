
#include <stdio.h>
#include <stdlib.h>
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "usartf0.h"
#include <math.h>
#include <string.h>
#include "stm32f0xx_adc.h"
#include "adc.h"
#include "SPILCD.h"
#include "table.h"


static const uint8_t array[640];
static uint8_t disp_array[320];

uint8_t* array_address;
uint8_t trig_val = 0x02;
int counter_search = 0;
int half_lim = 640;
int counter = 0;
int i;
uint16_t time_per = 32;

uint16_t COLOR_AXIS = RED;
uint16_t COLOR_GRAPH = WHITE;
uint16_t COLOR_BACKGROUND = BLACK;


void DrawGrid() {
	setDisplay(0, 150, 250, 10, BLUE);
	setDisplay(120, 0, 10, 320, BLUE);
}

void writeWord(char word [],  int x, int y){

	for(int i = 0; word[i] != '\0'; i++){

		dispChar(x, y, word[i], MAGENTA, BLACK, 2);
		x += 20;
	}
}


void writeNum(double num, int x, int y){

	char word[4];
	itoa((int)num, word, 10);
	writeWord(word, x, y);
}

//Battery variables
volatile double battery_mAh = 4400.0; // milliamp-hours (mAh)
volatile double battery_percent = 100.0;  // state-of-charge (percent)

double ah_quanta = 0.17067759; // mAh for each INT
double percent_quanta; // calculate below

void EXTI0_1_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0) != 0){
        EXTI_ClearITPendingBit(EXTI_Line0);
        uint8_t POL = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1);

        if(POL){
        	battery_mAh += ah_quanta;
        	battery_percent += percent_quanta;
        }else{
        	battery_mAh -= ah_quanta;
        	battery_percent -= percent_quanta;
        }
    }
}



void AisleNum(int screen){
	int left = 0;

	lcd_clear(WHITE);

	char Aisle_A[] = "Aisle A";
    char Aisle_B[] = "Aisle B";
    char Aisle_C[] = "Aisle C";
    //writeNum(battery_percent, 200, 200);
	if (screen == 1){
		writeWord("Aisle A",  30, 200); //dairy
	}
	else if (screen == 2){
		writeWord("Aisle B",  30, 200); //meat
	}
	else if (screen == 3){
		writeWord("Aisle C",  30, 200); //
	}
	setup_adc();
	setup_gpioy();
	int y;
	while(!left){ //read touch
		y = read_y();
		y = (y / 4096) * 3.3;

		if(y > 1.6 && y < 3.3 ){ //LEFT YLED
			left = 1;
		}
	}
	displayHome();

}


int main(void)
{

    percent_quanta = 1.0/(battery_mAh/1000.0*5859.0/100.0);

    GPIO_InitTypeDef config;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, 1);


    //GPIOC Pin1
    config.GPIO_Pin = 2;
    config.GPIO_Mode = 0;
    config.GPIO_PuPd = 0;
    GPIO_Init(GPIOC, &config);

    //Gpioc Pin0
    config.GPIO_Pin = 1;
    config.GPIO_Mode = 0;
    config.GPIO_PuPd = 0;
    GPIO_Init(GPIOC, &config);

    //Interrupt
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, 1);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, 0);
    EXTI_InitTypeDef initEXTI;
    initEXTI.EXTI_Line = 1;
    initEXTI.EXTI_Mode = 0;
    initEXTI.EXTI_Trigger = 12;
    initEXTI.EXTI_LineCmd = 1;
    EXTI_Init(&initEXTI);

    //NVIC
    NVIC_InitTypeDef initNVIC;
    initNVIC.NVIC_IRQChannel = 5;
    initNVIC.NVIC_IRQChannelPriority = 0x03;
    initNVIC.NVIC_IRQChannelCmd = 1;
    NVIC_Init(&initNVIC);

    GPIOAinit();
    NVIC_Configuration();

    SPIinit();
    InitGpioUsart();
    InitUsart1();
    begin();

    startTable();

    //writeCommand(ILI9341_SWRESET);
    	//writeCommand(ILI9341_NORON);

    	//writeCommand(ILI9341_PASET);
    	//writeCommand(ILI9341_RAMWR);
    	setAddressWindow(0, 0, 70, 100);

		displayHome();


    	//ADC
    	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; //on board LEDS
    	GPIOC->MODER &= ~(0x3 << (2*9));//left
    	GPIOC->MODER &= ~(0x3 << (2*8));//right
    	GPIOC->MODER |= (0x1 << (2*9));
   		GPIOC->MODER |= (0x1 << (2*8));

   		//breadboard LEDS
    	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //on board LEDS
    	GPIOA->MODER &= ~(0x3 << (2*9));//top
    	GPIOA->MODER &= ~(0x3 << (2*10));//bottom
    	GPIOA->MODER |= (0x1 << (2*9));
    	GPIOA->MODER |= (0x1 << (2*10));

    		int TR = 0;
    		int TL = 0;
    		int BR = 0;
    		int BL = 0;

    		int top = 0;
    		int bottom = 0;
    		int left = 0;
    		int right = 0;

    		setup_adc();

    		double x = 0.0;
    		double y = 0.0;
    		int cntx = 0;
    		int cnty = 0;


    		while(1){
				if(battery_percent < 20){
					GPIOA->ODR |= 1 << 9;
				}
				else{
					 GPIOA -> ODR &= ~(1 << 9);
				}
    		   setup_gpiox();
    		   nano_wait(40000000);
    		   x = read_x(); //READING TOP AND BOTTOM
    		   x = (x / 4096) * 3.3;

    		   if(x > 1.7 && x < 3.3){ //BOTTOM green LED
    			   bottom = 1;
    		   }
    		   else if(x > 0.5 && x < 1.3){ //TOP blue LED
    			   top = 1;
    		   }
    		   else{
    			   bottom = 0;
    			   top = 0;
    		   }

    		   cntx++;

    		   setup_gpioy(); //READING RIGHT AND LEFT

    		   nano_wait(40000000);

    		   y = read_y();
    		   y = (y / 4096) * 3.3;

    		   if(y > 1.8 && y < 3.3 ){ //LEFT YLED
    			   left = 1;
    		   }
    		   else if(y > 0.4 && y < 1.4){ //RIGHT GLED
    			   right = 1;
    		   }
    		   else{
    			   left = 0;
    			   right = 0;
    		   }


    		   cnty++;

    			TR = top & right;
    			TL = top & left;
    			BR = bottom & right;
    			BL = bottom & left;
				left = 0;
    			if(TR){ //DAIRY
					GPIOC->ODR |= 1 << 8; //blue led
    		    	lcd_clear(WHITE);
					writeWord("Aisle A",  30, 200);

					setup_gpioy();
					while(!left){ //read touch
						y = read_y();
						y = (y / 4096) * 3.3;

						if(y > 1.6 && y < 3.3 ){ //LEFT YLED
							left = 1;
						}
					}
					displayHome();
    			}
    			else if(TL){ //MEATS
					GPIOC->ODR |= 1 << 9; //green led
					lcd_clear(WHITE);
					writeWord("Aisle B",  30, 200);

					setup_gpioy();
					while(!left){ //read touch
						y = read_y();
						y = (y / 4096) * 3.3;

						if(y > 1.6 && y < 3.3 ){ //LEFT YLED
							left = 1;
						}
					}
					displayHome();
    			}
    			else if(BL){ //BREAD
					GPIOA->ODR |= 1 << 9; //PA9
    		    	lcd_clear(WHITE);
					writeWord("Aisle C",  30, 200);

					setup_gpioy();
					while(!left){ //read touch
						y = read_y();
						y = (y / 4096) * 3.3;

						if(y > 1.6 && y < 3.3 ){ //LEFT YLED
							left = 1;
						}
					}
					displayHome();
    			}
    			else if(BR){ //BATT.
					GPIOA->ODR |= 1 << 10; //PA10
					lcd_clear(WHITE);
					writeNum(battery_percent, 200, 200);

					setup_gpioy();
					while(!left){ //read touch
						y = read_y();
						y = (y / 4096) * 3.3;

						if(y > 1.6 && y < 3.3 ){ //LEFT YLED
							left = 1;
						}
					}
					displayHome();
    			}
				else{
					GPIOA -> ODR &= ~(1 << 9);
    				GPIOA -> ODR &= ~(1 << 10);
    				GPIOC -> ODR &= ~(1 << 9);
    				GPIOC -> ODR &= ~(1 << 8);
    			}
    		}
}
