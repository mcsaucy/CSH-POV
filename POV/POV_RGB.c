//POV DISPLAY
//REVISION
//-->RGB SUPPORT
//-->MORE EFFICIENT
//-->DYNAMIC DELAY
//
//JOSH MCSAVANEY

#define RAINBOW
//#define COLOR 0xFFDD00UL

#define MLEN 64  	// set the max number of characters (NOTE: INCLUDES NULL-TERMINATOR)
#define DELAY 50000     // delay for leds
#define LTRGAP 0	        // sets the number of gaps between characters

#define F_CPU 16000000UL
#define sbi(x,y) (x) |= (1 << (y))
#define cbi(x,y) (x) &= ~(1 << (y))
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)
#define USART_BAUDRATE 9600 
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) 

//#define BLIND_ME
#define BDIV 4		//scales brighness down (brighness/BDIV)

#define MAGIC            //what really makes this whole thing work

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonts.h"
#include "pwm.h"

char message [MLEN] = "/\\";
volatile char mbuf [MLEN] = "\0";
volatile int bctr = 0;

typedef struct
{
	uint8_t red;
	uint8_t grn;
	uint8_t blu;
} color_t;

void setup(void);
color_t HSVtoRGB(float);
int main(void);

int _DDRD, _DDRC, _DDRB;
color_t HSVtoRGB(float h)
{
	int i;
        int s = 1;
        int v = 1;
	float f, q, t, r, g, b;
	r = g = b = 0;
	h /= 60;			// sector 0 to 5
	i = h;
	f = h - i;			// factorial part of h
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );
	switch( i ) {
		case 0:
			r = v;
			g = t;
			break;
		case 1:
			r = q;
			g = v;
			break;
		case 2:
			g = v;
			b = t;
			break;
		case 3:
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			b = v;
			break;
		default:
			r = v;
			b = q;
			break;
	}
    
    color_t color = {255*r, 255*g, 255*b};


    return color;
}

ISR(USART_RX_vect)
{
        mbuf[bctr] = UDR0;
        if (mbuf[bctr] == '\n' || mbuf[bctr] == '\r' || bctr + 1 == MLEN || mbuf[bctr] == '\0')
        {
		if (mbuf[bctr] == '\n' || mbuf[bctr] == '\r') mbuf[bctr] = 0;
                for(uint8_t j = 0; j < bctr; j++)
                {
                        while (!(UCSR0A & (1 << UDRE0)));
                        UDR0 = mbuf[j];
                }
                bctr = 0;
                UCSR0B &= ~(1 << RXEN0);
		memcpy(message, mbuf, MLEN);
        }
        else bctr++;
}

int main()
{

       	_DDRC = 63;//B00111111;
       	_DDRB = 14;//B01110;
       	_DDRD = 192;

       	DDRD |= _DDRD;
       	DDRC |= _DDRC;
       	DDRB |= _DDRB;

       	TCCR1A = (1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0) | (1<<WGM10);
       	TCCR1B = (1<<WGM12) | (1<<CS10);

       	TCCR2A = (1<<COM2A1) | (1<<COM2A0) | (1<<COM2B1) | (1<<COM2B0) | (1<<WGM20) | (1<<WGM21);
       	TCCR2B = (1<<CS20);
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);   // Turn on the transmission and reception circuitry 
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
 
	UBRR0H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register 
	UBRR0L = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register 
	sei();

	#ifdef RAINBOW
	int hue = 0;
	#endif

	while (1)
	{
		UCSR0B |= (1 << RXEN0);
	       //iterates through each char of the message
	       for (int k = 0; k < strlen(message); k++)
	       {
	
	               //iterating through led columns
	               for (int i = 0; i < 5; i++)
	               {
	                      unsigned long chars = pgm_read_byte_near(charSet[(int)(message[k])] + i);
	
	                       //updates pin registers
	                       PORTD = (chars & DDRD);
	                       PORTC = (chars & DDRC);
	                       
	                       _delay_us(DELAY);
	                      
			       color_t color; 
			       #ifdef RAINBOW
	                       color = HSVtoRGB(hue);
			       hue ++;
			       hue %= 360;
			       #elif defined COLOR
			       color.red = (uint8_t)(COLOR >> 16 % 255);
			       color.grn = (uint8_t)(COLOR >> 8 % 255);
			       color.blu = (uint8_t)(COLOR >> 0 % 255);
			       #else
			       color.red = 128;
			       color.grn = 64;
			       color.blu = 32;
			       #endif

   			       #ifndef BLIND_ME
    			       color.red /= BDIV;
    			       color.grn /= BDIV;
    			       color.blu /= BDIV;
    			       #endif
    
    			       aWrite(9, color.red);
   			       aWrite(10, color.grn);
  			       aWrite(11, color.blu);
	
	               }
	               PORTD = ~_DDRD;
	               PORTC = ~_DDRC;
	               _delay_us(LTRGAP * DELAY/2);
	
	       } // end message print loop
	}
}

/*
int x = 0;
//Reads in from serial to update the message on the fly
void reader()
{

	// send data only when you receive data:
	while (Serial.available())
        {
		// read the incoming byte:
		buffer[x] = Serial.read();
                Serial.print(buffer[x]);
                //#ifdef DEBUG
                //      Serial.println(i);
                //#endif
                
                int index = 0;
                
                if(buffer[x] == '\n' || buffer[x] == '\r' || x >= sizeof(buffer))
                {
                        #ifdef DEBUG
                              Serial.println("Well, we got a \\r...");
                        #endif
                        
                        //buffer[x] = '\0';
                        
                        for(int n = 0; n < HORIZ_REZ; n++)
                        {
				message[index] = buffer[n];
                                index++;
                                      
                        }
                        
                        message[index] = '\0';
                        
                        for(int j = 0; j < sizeof(buffer); j++)
                        {
                                buffer[j] = 0;
                        }
                        
                        x = 0;
                        Serial.flush();
                        
                        //Print success message
                        Serial.print("\n\t*Message updated to \"");
                        Serial.print(message);
			Serial.print("\n");
                        return;
                }
                x++;
        }
}
*/
