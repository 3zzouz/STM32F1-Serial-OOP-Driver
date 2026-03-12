#include <stdint.h>

//GPIO BASE ADDRESSES REGISTERS
#define   GPIOA_BASE	  0x40010800
#define   GPIOB_BASE	  0x40010C00
#define   GPIOC_BASE	  0x40011000
#define   GPIOD_BASE	  0x40011400

#define		RCC_BASE			(0x40021000)


//define Pointers to GPIO Strcutures 
#define GPIOA  ((GPIO_Typedef*) GPIOA_BASE)
#define GPIOB  ((GPIO_Typedef*) GPIOB_BASE)
#define GPIOC  ((GPIO_Typedef*) GPIOC_BASE)
#define GPIOD  ((GPIO_Typedef*) GPIOD_BASE)

#define RCC     ((RCC_Typedef*) RCC_BASE)


//Define GPIO_Typedef strcuture containing The GPIO Registers
typedef struct  {

  uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
}
GPIO_Typedef;

//Define GPIO_Typedef strcuture containing The GPIO Registers

typedef struct  {

  uint32_t CRL; //0
	uint32_t CRH; //4
	uint32_t IDR; //8
	uint32_t ODR; //0C
	uint32_t BSRR; //10
	uint32_t BRR;  //14
	uint32_t APB2ENR; //18
}
RCC_Typedef;