#include "stm32f10x.h"
#include "Serial_Mode_Name.h"
#include "stm32f10x_dma.h"

#ifndef __STM32_WRAPPER_GPIO_H
#define __STM32_WRAPPER_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

	
/* =======================================*/
/* 1 : Functions For PinAsInput Class --- */
/*----------------------------------------*/
	
	
static void GPIO_Pin_init(GPIO_TypeDef* GPIOx ,uint16_t Pin,GPIOMode_TypeDef mode );
static config_typedef get_serial_config (UartConfig config);
static uint32_t get_serial_speed (UartSpeed speed);
static uint16_t get_serial_mode (UartMode mode);
static uint16_t get_serial_comport (UartComport comport);
USART_TypeDef* _serial_init(uint8_t COMPORT, uint8_t PinTX, uint8_t PinRX ,uint16_t Speed, uint8_t Config, uint8_t Mode);


void configInterrupts(USART_TypeDef* USARTx,uint16_t mode);
void itprintchaine(USART_TypeDef* USARTx, char* chaine, int length);
char* itreadchaine(USART_TypeDef* USARTx, int length);
	
void configDMA(USART_TypeDef* USARTx,int isRead,int length);	
void dmaprintchaine(USART_TypeDef* USARTx, char* chaine, int length);
char* dmareadchaine(USART_TypeDef* USARTx, int length);
/*==========================================*/


	
/* --- 2 : Common Functions ---- */

/*  Get the GPIOx From PinName  */
static GPIO_TypeDef* get_gpioport (PinName pin);
	

#ifdef __cplusplus
}
#endif


#endif //__STM32_WRAPPER_GPIO_H
