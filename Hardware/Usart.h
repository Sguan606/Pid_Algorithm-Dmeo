#ifndef __USART_H
#define __USART_H


void Usart_Init(void);
BlueTooth_SendByte(uint8_t Byte);
uint8_t RX_DataGet(void);
void BlueTooth_SendInt(int number);
void BlueTooth_SendFloatAsString(float value);
void USART3_IRQHandler(void);



#endif
