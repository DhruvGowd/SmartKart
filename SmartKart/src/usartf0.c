/*
 * usartf0.c
 *
 *  Created on: Apr 10, 2020
 *      Author: DhruvG
 */

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include <string.h>
//#include "362_GFX.h"
#include "usartf0.h"
#include "adc.h"
#include "SPILCD.h"
#include "table.h"

char item[30];
char *items[100];
char *aisle[100];
char *price[100];
Product table [100];
int idx = 75;
int i = 0;

void startTable(){
    initializeArrays(items, aisle, price);
    initTable(table, items, aisle, price);
}
void delay(unsigned int time) {
	for (time; time > 0; time--);
}

void NVIC_Configuration(void){
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void InitGpioUsart(void){
	//ENABLING CLOCK TO GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

	GPIOC->MODER |= 0x1 << 18;
	//CONFIGURING PB6 & PB7 TO ALTERNATE FUNCTION TO USE USART
	GPIOB->MODER &= ~(0x3 << (6*2));
	GPIOB->MODER &= ~(0x3 << (7*2));
	GPIOB->MODER |= 0x2 << (6*2);//TX
	GPIOB->MODER |= 0x2 << (7*2);//RX

	//Set AFR to AFR0
	GPIOB->AFR[0] &= ~0xFF000000;
	GPIOB->AFR[0] |=  0x00000000;
}

void USARTSend(const unsigned char *Buffer, unsigned long Count)
{
    while(Count--)
    {
        USART_SendData(USART1, (uint16_t) *Buffer++);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }
}

void USART1_IRQHandler(void){
	GPIOC->ODR ^= 1<<9;
	uint16_t code = 0;
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET){
		code = USART_ReceiveData(USART1);
		if(code != '\r'){
			item[i++] = code;
		}
		if (code == '%'){
			setAddressWindow(0, 0, 70, 300);
			lcd_clear(WHITE);
			delay(100);
			item[i-1] = '\0';
			idx = getInfoIndex(table, item);
			writeWord(table[idx].location, 30, 150);
			writeWord(table[idx].value, 30, 175);
			writeWord(item, 30, 200);
			char z[2];
			z[0] = idx + '0';
			z[1] = '\0';
//			writeWord(z,30, 125 );
//			writeNum((float) idx, 200, 200);
			i = 0;
			//for(int j = 0; j < 30; j++){item[j] = '0';}
			memset(item, 0, 30);
			nano_wait(99999999999999);
			nano_wait(99999999999999);
			nano_wait(99999999999999);
			nano_wait(99999999999999);
			displayHome();
		}

	}
}

void InitUsart1(void){
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
//	USART1->CR1 &= USART_CR1_M;
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
