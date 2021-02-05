#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"

#include "avr/interrupt.h"
#include "AVR_UART_REG.h"


#include <avr/delay.h>


#define FOCS 1000000
#define BAUD 9600
#define SS FOCS/16/BAUD-1

void USART_INT(uint32_t ss)
{
	UBRRH = (uint8_t)(ss>>1);
	UBRRL = (uint8_t)ss;

	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);

	SET_BIT(UCSRC,URSEL);
	SET_BIT(UCSRC,USBS);
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);


}


uint8_t UART_REC(void)
{
	while(GET_BIT(UCSRA,RXC)==0)
	{

	}

	return UDR;
}

int main()
{
	    USART_INT(SS);
		MCAL_DIO_u8SetPinDir(PORTB,PIN0,DIO_OUTPUT);
		uint8_t MICRO=UART_REC();

		if(MICRO=='1')
		{
			MCAL_DIO_u8SetPinValue(PORTB,PIN0,DIO_HIGH);
		}
}
