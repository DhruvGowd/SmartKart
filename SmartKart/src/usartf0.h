/*
 * usartf0.h
 *
 *  Created on: Apr 10, 2020
 *      Author: DhruvG
 */

#ifndef USARTF0_H_
#define USARTF0_H_
void delay(unsigned int time);
void InitGpioUsart(void);
void USARTSend(const unsigned char *Buffer, unsigned long Count);
void USART1_IRQHandler(void);
void InitUsart1(void);
void startTable(void);


#endif /* USARTF0_H_ */
