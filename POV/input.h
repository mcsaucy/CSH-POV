#ifndef INPUT_H
#define INPUT_H

#include <avr/interrupt.h>
#include <util/delay.h>

ISR(USART_RX_vect)
{
        uint8_t rx;
        rx  = UDR0;
        msg[i] = rx;
        if (msg[i] == '\n' || msg[i] == '\r' || i + 1 == SIZE || msg[i] == '\0')
        {
                for(uint8_t j = 0; j < i; j++)
                {
                        while (!(UCSR0A & (1 << UDRE0)));
                        UDR0 = msg[j];
                }
                i = 0;
                UCSR0B &= ~(1 << RXEN0);
	}
	else i++;
}

#endif
