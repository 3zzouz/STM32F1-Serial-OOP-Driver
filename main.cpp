#include "stm32f10x.h"
#include "Serial.h"
#include "string.h"

using namespace OOlayer;

// Definition of static member variable
char *receivedData;
char* stringToSend = (char*)"Test";
int main()
{
	Serial MyPortCom = Serial();
	//receivedData = MyPortCom.readchaine(8);
	//receivedData = MyPortCom.ITreadchaine(8);
	//receivedData = MyPortCom.DMAreadchaine(8);
	
	//MyPortCom.printchaine(stringToSend,strlen(stringToSend));
	//MyPortCom.ITprintchaine(stringToSend,strlen(stringToSend));
	MyPortCom.DMAprintchaine(stringToSend,strlen(stringToSend));
	while (1)
	{
		
	}
}
