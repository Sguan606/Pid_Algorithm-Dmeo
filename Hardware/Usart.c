#include "stm32f10x.h"
#include "Usart.h"


void Usart_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART3,&USART_InitStructure);

    USART_Cmd(USART3,ENABLE);
}



BlueTooth_SendByte(uint8_t Byte)
{
    USART_SendData(USART3,Byte);
    while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET);
}

uint8_t RX_DataGet(void)
{
    return RX_Date;
}

void BlueTooth_SendInt(int number)
{
    char buffer[12];  // 用于存储整数转换后的字符串，假设int最大为10位+1个符号位+1个结尾符号位
    sprintf(buffer, "%d", number);  // 将整数转为字符串

    // 逐个字节发送
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        BlueTooth_SendByte(buffer[i]);  // 使用你原本的 Serial_SendByte 函数发送每个字符
    }
}

void BlueTooth_SendFloatAsString(float value)
{
    char buffer[16];  
    snprintf(buffer, sizeof(buffer), "%.3f", value); 

    for (int i = 0; buffer[i] != '\0'; i++)
    {
        BlueTooth_SendByte(buffer[i]);
    }
}

void USART3_IRQHandler(void)
{
    if ((USART_GetITStatus(USART3,USART_IT_RXNE) == SET))
    {
        RX_Date = USART_ReceiveData(USART3);
    }
}



