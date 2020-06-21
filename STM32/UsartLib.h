#ifndef  USARTLIB_H
#define  USARTLIB_H

#include "usart.h"
#include "UsartTypes.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_usart.h"

extern "C" {
	void USART1_IRQHandler(); 
}

class Usart {

public:

	/**
	*\br Initiate Usart object with Usartx instance 
	*@param   USARTx USART_TypeDef *Usartx
	*\retval Usart object
	*/
	Usart();
	
	/**
	*\br write byte to transmit register
	*\p byte, Byte to send
	*\retval NONE
   */
	void WriteByte(unsigned char byte);

	/**
	*\br Send Bytes via Usartx 
	*\p bytes, Pointer to start of array to send
	*\p count, Number of bytes to send
	*\retval NONE
	*/
	void WriteBytes(uint8_t* bytes, int count);
 
	/**
	*\br read Byte from receive register
	*\retval Byte from receive register
	*\att BLOCKING CALL until character is received
	*/
	uint8_t ReadByte();

private:
	USART_TypeDef* instance;
};
#endif

