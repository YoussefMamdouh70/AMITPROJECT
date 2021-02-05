#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "INT_interface.h"
#include "S_SEGMENT.h"
#include "TIMER_interface.h"
#include "AVR_TIMER_REG.h"
#include "AVR_INT_REG.h"
#include "avr/interrupt.h"
#include "AVR_UART_REG.h"

#include  "AVR_INT_REG.h"
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

void UART_TRANS(uint8_t data)
{
	while(GET_BIT(UCSRA,UDRE)!=1)
	{
		UDR=data;
	}
}

int main()
{
    USART_INT(SS);
	MCAL_DIO_u8SetPinDir(PORTA,PIN0,DIO_OUTPUT);
	_delay_ms(2000);
	MCAL_DIO_u8SetPinValue(PORTA,PIN0,DIO_HIGH);
	if(GET_BIT(PORTA,PIN0)==1)
	{
		UART_TRANS('a');
	}


}










