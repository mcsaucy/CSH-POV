#ifndef INPUT_H
#define INPUT_H

#include <avr/interrupt.h>

//looking at this 6 mongth later, having a busy wait in an ISR was a HORRIBLE idea
ISR(USART_RX_vect)
{
        uint8_t rx;
        rx  = UDR0;
        msg[i] = rx;
        if (msg[i] == '\n' || msg[i] == '\r' || i + 1 == SIZE || msg[i] == '\0')
        {
                for(uint8_t j = 0; j < i; j++)
                {
			//this was pretty much my first ever ISR
                        while (!(UCSR0A & (1 << UDRE0)));
			//now that everything is screwed timing wise, continue
                        UDR0 = msg[j];
                }
                i = 0;
                UCSR0B &= ~(1 << RXEN0);
	}
	else i++;
}

#endif
