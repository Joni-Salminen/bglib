#include "UsartLib.h"


Usart::Usart() {}

void Usart::WriteByte(unsigned char byte) {
	/* wait data register empty */
	while (!(USART2->SR & USART_SR_TXE)){}
	USART2->DR = byte;  
}

void Usart::WriteBytes(uint8_t *bytes, int count) {
  while (count--)
    WriteByte(*bytes++);	
}

uint8_t Usart::ReadByte() {
  /* wait data register not empty */
	while (!(USART2->SR & USART_SR_RXNE)) {}	
	return USART2->DR;
}


	
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	uint16_t PIN_AF;
	
	/* Check if periephal is Usart or Uart to determinate pin alternative function */
	if (IsUsart)
		PIN_AF = LL_GPIO_AF_7;
	else
		PIN_AF = LL_GPIO_AF_8;
	
	/* Enable clock for GPIO port */
	if (RX_PIN_PORT || TX_PIN_PORT == GPIOA)
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	else if (RX_PIN_PORT || TX_PIN_PORT == GPIOB)
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	else if (RX_PIN_PORT || TX_PIN_PORT == GPIOC)
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
	
	/* if pins in same port we can initialise in one go */		
	if (RX_PIN_PORT == TX_PIN_PORT) {				
		GPIO_InitStruct.Pin = TX_pin | RX_pin;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
		GPIO_InitStruct.Alternate = PIN_AF;
		LL_GPIO_Init(RX_PIN_PORT, &GPIO_InitStruct);	
	}
	else {			
		GPIO_InitStruct.Pin = TX_pin;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
		GPIO_InitStruct.Alternate = PIN_AF;
		LL_GPIO_Init(TX_PIN_PORT, &GPIO_InitStruct);	
		
		GPIO_InitStruct.Pin = RX_pin;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
		GPIO_InitStruct.Alternate = PIN_AF;
		LL_GPIO_Init(RX_PIN_PORT, &GPIO_InitStruct);	
	}		
}



