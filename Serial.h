/*********************************************************************************/
/* OO STM32 Library : PinAsInput CLASS DECLARATION To configure GPIO Pins as Input
	 E.D INSA TNov 2021
		  Default Constructor: Floating

		Use:  PinAsInput  ObjectName (PA_i) ,
			  where X is for GPIOX (A, B, C or D)
					i is the pin Number (0 to 15)

		Example:  PinAsInput MyButton (PA_0);
************************************************************************************/

#include <stm32_wrapper_serial.h>
#include <stdlib.h>
#include <string.h>

namespace OOlayer
{
	class Serial
	{
		USART_TypeDef *USARTx;

	public:
		Serial()
		{
			this->USARTx = _serial_init(ComportDefault, 0X09, 0X0A, SpeedDefault, ConfDefault, ModeDefault);
		}
		Serial(UartComport COMPORT, PinName PinTX, PinName PinRX)
		{
			this->USARTx = _serial_init(COMPORT, PinTX, PinRX, SpeedDefault, ConfDefault, ModeDefault);
		}
		Serial(UartComport COMPORT, PinName PinTX, PinName PinRX, UartSpeed Speed)
		{
			this->USARTx = _serial_init(COMPORT, PinTX, PinRX, Speed, ConfDefault, ModeDefault);
		}
		Serial(UartComport COMPORT, PinName PinTX, PinName PinRX, UartSpeed Speed, UartConfig Config)
		{
			this->USARTx = _serial_init(COMPORT, PinTX, PinRX, Speed, Config, ModeDefault);
		}
		Serial(UartComport COMPORT, PinName PinTX, PinName PinRX, UartSpeed Speed, UartConfig Config, UartMode Mode)
		{
			this->USARTx = _serial_init(COMPORT, PinTX, PinRX, Speed, Config, Mode);
		}

		/***** Read the input, represented as 0 or 1 (int)
		 *
		 *  @returns
		 *    An integer representing the state of the input pin,
		 *    0 for logical 0, 1 for logical 1
		 */

		GPIO_TypeDef *get_GPIO()
		{
			if ((USARTx == USART1) || (USARTx == USART2))
				return GPIOA;
			else
				return GPIOB;
		}
		void printchaine(char *chaine, int length)
		{
			int i;
			char Char_tosend;
			for (i = 0; i < length; i++)
			{
				while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
					; // wait until USART2 TX Register is Empty
				Char_tosend = chaine[i];
				USART_SendData(USARTx, Char_tosend); // Send Data
			}
		}

		char *readchaine(int length)
		{
			int nbChar = 0;
			char receivedChar;
			char *buffer = (char *)malloc(length + 1);
			int counter;
			while (nbChar < length)
			{
				while (USART_GetFlagStatus(this->USARTx, USART_FLAG_RXNE) == RESET)
				{
					counter++;
				} // wait until USART1 RX Register is not Empty
				receivedChar = USART_ReceiveData(this->USARTx);
				buffer[nbChar++] = receivedChar; // read character
			}
			return buffer;
		}

		void ITprintchaine(char *chaine, int length)
		{
			itprintchaine(this->USARTx, chaine, length);
		}

		char *ITreadchaine(int length)
		{
			return itreadchaine(this->USARTx, length);
		}
		
		void DMAprintchaine(char *chaine, int length)
		{
			dmaprintchaine(this->USARTx, chaine, length);
		}

		char *DMAreadchaine(int length)
		{
			return dmareadchaine(this->USARTx, length);
		}
	}; // Class End
} // namespace
