/*
* SignalGen.c
*
* Created: 24/03/2018 14:23:12
* Author : Ulric
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void USART_Init(unsigned int);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);

int main(void)
{
	USART_Init(MYUBRR);
	
	while (1)
	{
		if (USART_receive() == '1')
		{
			for (int i = 0; i < 256; i++ )
			{
				USART_send((unsigned char)i);
				_delay_ms(500);
			}
		}
	}
}

void USART_Init( unsigned int ubrr)
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

unsigned char USART_receive(void)
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void USART_send( unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void USART_putstring(char* StringPtr)
{	
	while(*StringPtr != 0x00)
	{
		USART_send(*StringPtr);
		StringPtr++;
	}
}

