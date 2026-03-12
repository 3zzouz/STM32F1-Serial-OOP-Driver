#include "stm32_wrapper_serial.h"
#include <stdlib.h>
static uint16_t get_serial_mode(UartMode mode)
{
	switch (mode)
	{
	case 1:
		return USART_Mode_Tx;
	case 2:
		return USART_Mode_Rx;
	case 3:
		return USART_Mode_Rx | USART_Mode_Tx;
	default:
		return USART_Mode_Rx | USART_Mode_Tx;
	}
}
static uint16_t get_serial_comport(UartComport comport)
{
	switch (comport)
	{
	case 1:
		return USART_HardwareFlowControl_RTS;
	case 2:
		return USART_HardwareFlowControl_None;
	case 3:
		return USART_HardwareFlowControl_CTS;
	default:
		return USART_HardwareFlowControl_None;
	}
}

static uint32_t get_serial_speed(UartSpeed speed)
{
	switch (speed)
	{
	case 1:
		return 9600;
	case 2:
		return 19200;
	case 3:
		return 115200;
	default:
		return 9600;
	}
}
static config_typedef get_serial_config(UartConfig config)
{
	config_typedef conf;

	switch (config)
	{
	case 1:
		conf.WordLength = USART_WordLength_8b;
		conf.Parity = USART_Parity_No;
		conf.StopBits = USART_StopBits_1;
		break;
	case 2:
		conf.WordLength = USART_WordLength_8b;
		conf.Parity = USART_Parity_No;
		conf.StopBits = USART_StopBits_2;
		break;
	case 3:
		conf.WordLength = USART_WordLength_8b;
		conf.Parity = USART_Parity_Even;
		conf.StopBits = USART_StopBits_1;
		break;
	case 4:
		conf.WordLength = USART_WordLength_8b;
		conf.Parity = USART_Parity_Even;
		conf.StopBits = USART_StopBits_2;
		break;
	case 5:
		conf.WordLength = USART_WordLength_8b;
		conf.Parity = USART_Parity_Odd;
		conf.StopBits = USART_StopBits_1;
		break;
	case 6:
		conf.WordLength = USART_WordLength_8b;
		conf.Parity = USART_Parity_Odd;
		conf.StopBits = USART_StopBits_2;
		break;
	case 7:
		conf.WordLength = USART_WordLength_9b;
		conf.Parity = USART_Parity_No;
		conf.StopBits = USART_StopBits_1;
		break;
	case 8:
		conf.WordLength = USART_WordLength_9b;
		conf.Parity = USART_Parity_No;
		conf.StopBits = USART_StopBits_2;
		break;
	case 9:
		conf.WordLength = USART_WordLength_9b;
		conf.Parity = USART_Parity_Even;
		conf.StopBits = USART_StopBits_1;
		break;
	case 10:
		conf.WordLength = USART_WordLength_9b;
		conf.Parity = USART_Parity_Even;
		conf.StopBits = USART_StopBits_2;
		break;
	case 11:
		conf.WordLength = USART_WordLength_9b;
		conf.Parity = USART_Parity_Odd;
		conf.StopBits = USART_StopBits_1;
		break;
	case 12:
		conf.WordLength = USART_WordLength_9b;
		conf.Parity = USART_Parity_Odd;
		conf.StopBits = USART_StopBits_2;
		break;
	default:
		conf.WordLength = USART_WordLength_8b;
		conf.Parity = USART_Parity_No;
		conf.StopBits = USART_StopBits_1;
	}
	return conf;
}
// static methode to activate gpio pin
static void GPIO_Pin_init(GPIO_TypeDef *GPIOx, uint16_t Pin, GPIOMode_TypeDef mode)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	// Enable used GPIOs Clocks
	GPIO_InitStruct.GPIO_Pin = Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Mode = mode;
	GPIO_Init(GPIOx, &GPIO_InitStruct);
}

USART_TypeDef *_serial_init(uint8_t COMPORT, uint8_t PinTX, uint8_t PinRX, uint16_t Speed, uint8_t Config, uint8_t Mode)
{

	// get the serialID from PinName (0 for serialA, 1 for serialB, ...)
	int gpioId = (PinTX & 0xF0) >> 4;
	int pinIdTX = (PinTX & 0x0F);
	GPIO_TypeDef *gpio;
	uint16_t pinTX;
	uint16_t pinRX;
	switch (gpioId)
	{
	case 0:
		gpio = GPIOA;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		break;
	case 1:
		gpio = GPIOB;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		break;
	case 2:
		gpio = GPIOC;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		break;
	default:
		break;
	}
	switch (pinIdTX)
	{
	case 0:
		pinTX = GPIO_Pin_0;
		break;
	case 1:
		pinTX = GPIO_Pin_1;
		break;
	case 2:
		pinTX = GPIO_Pin_2;
		break;
	case 3:
		pinTX = GPIO_Pin_3;
		break;
	case 4:
		pinTX = GPIO_Pin_4;
		break;
	case 5:
		pinTX = GPIO_Pin_5;
		break;
	case 6:
		pinTX = GPIO_Pin_6;
		break;
	case 7:
		pinTX = GPIO_Pin_7;
		break;
	case 8:
		pinTX = GPIO_Pin_8;
		break;
	case 9:
		pinTX = GPIO_Pin_9;
		break;
	case 10:
		pinTX = GPIO_Pin_10;
		break;
	case 11:
		pinTX = GPIO_Pin_11;
		break;
	case 12:
		pinTX = GPIO_Pin_12;
		break;
	case 13:
		pinTX = GPIO_Pin_13;
		break;
	case 14:
		pinTX = GPIO_Pin_14;
		break;
	case 15:
		pinTX = GPIO_Pin_15;
		break;
	default:
		break;
	}
	pinRX = pinTX << 1;

	USART_InitTypeDef USART_InitStructure;
	// convert serialID to serialx
	uint16_t mode = get_serial_mode((UartMode)Mode);
	uint16_t speed = get_serial_speed((UartSpeed)Speed);
	config_typedef config = get_serial_config((UartConfig)Config);
	uint16_t comport = get_serial_comport((UartComport)COMPORT);

	if (mode == USART_Mode_Tx)
	{
		GPIO_Pin_init(gpio, pinTX, GPIO_Mode_AF_PP);
	}
	else if (mode == USART_Mode_Rx)
	{
		GPIO_Pin_init(gpio, pinRX, GPIO_Mode_IN_FLOATING);
	}
	else
	{
		GPIO_Pin_init(gpio, pinTX, GPIO_Mode_AF_PP);
		GPIO_Pin_init(gpio, pinRX, GPIO_Mode_IN_FLOATING);
	}

	USART_TypeDef *USARTx;
	switch (pinIdTX)
	{
	case 9:
		USARTx = USART1;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		break;
	case 2:
		USARTx = USART2;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		break;
	case 10:
		USARTx = USART3;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		break;
	default:
		break;
	}

	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength = config.WordLength;
	USART_InitStructure.USART_Parity = config.Parity;
	USART_InitStructure.USART_StopBits = config.StopBits;
	USART_InitStructure.USART_HardwareFlowControl = comport;
	USART_InitStructure.USART_Mode = mode;

	USART_Init(USARTx, &USART_InitStructure);
	USART_Cmd(USARTx, ENABLE);
	return USARTx;
}

void configInterrupts(USART_TypeDef *USARTx, uint16_t mode)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	uint8_t usart_irqn;
	if (USARTx == USART1)
		usart_irqn = USART1_IRQn;
	else if (USARTx == USART2)
		usart_irqn = USART2_IRQn;
	else
		usart_irqn = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannel = usart_irqn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USARTx, mode, ENABLE);
}

static char *tx_message;
static int tx_message_length = 0;
static int tx_message_index = 0;

static char *rx_buffer;
static int rx_length = 0;
static int rx_index = 0;

void itprintchaine(USART_TypeDef *USARTx, char *chaine, int length)
{
	tx_message = chaine;
	tx_message_length = length;
	tx_message_index = 0;
	configInterrupts(USARTx, USART_IT_TXE);
}

char *itreadchaine(USART_TypeDef *USARTx, int length)
{
	rx_buffer = (char *)malloc(length + 1);
	rx_length = length;
	rx_index = 0;
	configInterrupts(USARTx, USART_IT_RXNE);
	/*while(rx_length>rx_index){};*/
	return rx_buffer;
}

void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_TXE))
	{
		if (tx_message_index < tx_message_length)
		{
			USART1->DR = tx_message[tx_message_index++];
		}
		if (tx_message_index == tx_message_length)
		{
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		}
	}
	if (USART_GetITStatus(USART1, USART_IT_RXNE))
	{
		if (rx_index < rx_length)
		{
			rx_buffer[rx_index++] = USART1->DR;
		}
		if (rx_index == rx_length)
		{
			USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
			rx_buffer[rx_index] = '\0';
		}
	}
}

void USART2_IRQHandler(void)
{
	if (USART_GetITStatus(USART2, USART_IT_TXE))
	{
		if (tx_message_index < tx_message_length)
		{
			USART2->DR = tx_message[tx_message_index++];
		}
		if (tx_message_index == tx_message_length)
		{
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		}
	}
	if (USART_GetITStatus(USART2, USART_IT_RXNE))
	{
		if (rx_index < rx_length)
		{
			rx_buffer[rx_index++] = USART2->DR;
		}
		if (rx_index == rx_length)
		{
			rx_buffer[rx_index] = '\0';
			USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
		}
	}
}

void USART3_IRQHandler(void)
{
	if (USART_GetITStatus(USART3, USART_IT_TXE))
	{
		if (tx_message_index < tx_message_length)
		{
			USART3->DR = tx_message[tx_message_index++];
		}
		if (tx_message_index == tx_message_length)
		{
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		}
	}
	if (USART_GetITStatus(USART3, USART_IT_RXNE))
	{
		if (rx_index < rx_length)
		{
			rx_buffer[rx_index++] = USART3->DR;
		}
		if (rx_index == rx_length)
		{
			rx_buffer[rx_index] = '\0';
			USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
		}
	}
}

void configDMA(USART_TypeDef *USARTx, int isRX, int length)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStruct;
	uint8_t dma_irqn;
	uint16_t dma_req;
	DMA_Channel_TypeDef *dma_channel;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	if (USARTx == USART3)
	{
		if (!isRX)
		{
			dma_irqn = DMA1_Channel2_IRQn;
			dma_channel = DMA1_Channel2;
		}
		else
		{
			dma_channel = DMA1_Channel3;
			dma_irqn = DMA1_Channel3_IRQn;
		}
	}
	else if (USARTx == USART1)
	{
		if (!isRX)
		{
			dma_irqn = DMA1_Channel4_IRQn;
			dma_channel = DMA1_Channel4;
		}
		else
		{
			dma_channel = DMA1_Channel5;
			dma_irqn = DMA1_Channel5_IRQn;
		}
	}
	else
	{
		if (isRX)
		{
			dma_irqn = DMA1_Channel6_IRQn;
			dma_channel = DMA1_Channel6;
		}
		else
		{
			dma_irqn = DMA1_Channel7_IRQn;
			dma_channel = DMA1_Channel7;
		}
	}
	NVIC_InitStructure.NVIC_IRQChannel = dma_irqn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);

	if (isRX)
		dma_req = USART_DMAReq_Rx;
	else
		dma_req = USART_DMAReq_Tx;

	USART_DMACmd(USARTx, dma_req, ENABLE);

	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_BufferSize = length;
	if (isRX)
		DMA_InitStruct.DMA_MemoryBaseAddr = GPIOA->IDR;
	else
		DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&(GPIOA->IDR);
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(GPIOA->ODR);
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	if (isRX)
		DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	else
		DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_ITConfig(dma_channel, DMA_IT_TC, ENABLE);
	DMA_Init(dma_channel, &DMA_InitStruct);
	DMA_Cmd(dma_channel, ENABLE);
}

char* copietx;

void dmaprintchaine(USART_TypeDef *USARTx, char *chaine, int length)
{
	tx_message = chaine;
	copietx = tx_message;
	configDMA(USARTx, 0, length);
}

char *dmareadchaine(USART_TypeDef *USARTx, int length)
{
	rx_buffer = (char *)malloc(length + 1);
	configDMA(USARTx, 1, length);
	return rx_buffer;
}

void DMA1_Channel3_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA1_IT_TC3))
	{
		DMA_ClearITPendingBit(DMA1_IT_TC3);
	}
}
int transfer_count;
void DMA1_Channel5_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA1_IT_TC5))
	{
		DMA_ClearITPendingBit(DMA1_IT_TC5);
	}
}

void DMA1_Channel6_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA1_IT_TC6))
	{
		DMA_ClearITPendingBit(DMA1_IT_TC6);
	}
}
