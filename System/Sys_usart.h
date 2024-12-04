#ifndef __SYS_USART_H
#define __SYS_USART_H
#include "stdio.h"	
#include "sys.h" 


void uart1_init(u32 bound);					//串口1初始化函数
void USART1_IRQHandler(void);     	//串口1中断服务程序


#endif
