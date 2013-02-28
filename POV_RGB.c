//POV DISPLAY
//REVISION
//-->RGB SUPPORT
//-->MORE EFFICIENT
//-->DYNAMIC DELAY
//
//JOSH MCSAVANEY

#define SPINNING

#define RAINBOW
//#define COLOR 0x00FF00UL

#define MLEN 64		// set the max number of characters (NOTE: INCLUDES NULL-TERMINATOR)
#define DELAY 5000	// delay for leds
#define LTRGAP 0	// sets the number of gaps between characters

#define F_CPU 16000000UL
#define sbi(x,y) (x) |= (1 << (y))
#define cbi(x,y) (x) &= ~(1 << (y))
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)
#define USART_BAUDRATE 9600 
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) 
#define OF_PRO_LVL 4
//#define TALK_BACK_TO_ME

//#define BLIND_ME
#define BDIV 1		//scales brighness down (brighness/BDIV)

#define MAGIC		//what really makes this whole thing work

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonts.h"
#include "pwm.h"
#include "color.h"

char message [MLEN] = "><";
volatile uint8_t of_pro = 0; //Overflow protection
volatile uint8_t rctr = 0;
volatile uint16_t rLast = 0;
volatile uint16_t dLast = 0;
volatile uint16_t tDelay=100; 

volatile uint8_t tHigh = 0;
volatile uint8_t tLow = 0;

static volatile char sin_buf[MLEN];
static volatile char *sin_buf_w = sin_buf;

void setup(void);
color_t HSVtoRGB(float);
int main(void);

ISR(INT0_vect)
{
	tLow = tHigh;
	tHigh = TCNT1;
}

ISR(USART_RX_vect)
{
	*sin_buf_w = UDR0;
	if( *sin_buf_w  == '\r' || sin_buf_w == sin_buf+MLEN-1)
	{
		of_pro = OF_PRO_LVL;
		UCSR0B &= ~(1 << RXEN0);
	}
	else
	{
		#ifdef TALK_BACK_TO_ME
			while (!(UCSR0A & (1 << UDRE0)));
			UDR0 = *sin_buf_w;
		#endif
		sin_buf_w++;
	}
}

int main()
{

	_DDRC = 63;	//mask for LED control
	_DDRB = 48;	//mask for LED control

	DDRD |= 96;
	DDRC |= _DDRC;
	DDRB |= _DDRB | 8;	//allows for PWM output but doesn't affect masking for LED control

	TCCR0A = (1<<WGM00) | (1<<WGM01) | (1<<COM0B1) | (1<<COM0B0) | (1<<COM0A1) | (1<<COM0A0);
	TCCR0B = (1<<CS00);
	
	TCCR1B = (1<<CS10) | (1<<CS11);	//Timer used for delay calculation
	
	TCCR2A = (1<<COM2A1) | (1<<COM2A0) | (1<<WGM20) | (1<<WGM21);
	TCCR2B = (1<<CS20);

	UCSR0B |= (1 << RXEN0) | (1 << RXCIE0);   //Enable reception and associated interrupt
	#ifdef TALK_BACK_TO_ME
		UCSR0B |= (1 << TXEN0);	//Enable transmission
	#endif 
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
 
	UBRR0 = BAUD_PRESCALE;

	EICRA = (1<<ISC01);	//Configure PD2 (pin 4) as INT0 external interrupt to be tripped by the falling edge
	EIMSK = (1<<INT0);

	sei();

	#ifdef RAINBOW
	int hue = 0;
	#endif

	dLast = TCNT1;

	while (1)
	{
		if(of_pro == OF_PRO_LVL)
		{
			if(sin_buf_w>=sin_buf+MLEN)
			{
				sin_buf_w=sin_buf+MLEN-1;
			}
			*sin_buf_w = '\0';
			memcpy(message, (void *)sin_buf, MLEN);
			sin_buf_w = sin_buf;
		}

		if(of_pro>0) of_pro--;
		else UCSR0B |= (1 << RXEN0);

		//moving through the message
		#ifndef SPINNING
		for (int k = 0; k < strlen(message); k++) 
	    {
		#else
		for (int k = 0; k < MLEN; k++)
		{
		#endif
	        //iterating through led columns
			for (int i = 0; i < 5; i++)
	        {
				uint8_t chars = pgm_read_byte_near(charSet[(int)(message[k])] + i);
	
	           	//updates pin output registers
	            PORTB = ~((chars<<5 & (1<<PB5)) | (chars<<3 & (1<<PB4)));
	            PORTC = ~(chars>>2 & _DDRC);
	            
				#ifdef SPINNING
					tDelay = ((tHigh-tLow)%65535)/(MLEN*(5+LTRGAP));
					_delay_us(4*(tDelay-(TCNT1-dLast)%65535)); 
					dLast = TCNT1;
				#else
					_delay_us(DELAY);
				#endif
	                      
			    color_t color; 
			    #ifdef RAINBOW
	            	color = HSVtoRGB(hue);
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
    			    color.red *= BDIV;
    			    color.grn *= BDIV;
    			    color.blu *= BDIV;
    			#endif
    
    			aWrite(5, color.grn);
   			    aWrite(6, color.blu);
  			    aWrite(11, color.red);
		
	            }
	            PORTB = _DDRB;
	            PORTC = _DDRC;
				#ifdef SPINNING
	            	_delay_us(LTRGAP*4*(tDelay - ((TCNT1-dLast)%65535)));
					dLast = TCNT1;
				#else
					_delay_us(DELAY*LTRGAP);
				#endif
	
	       	} // end message print loop
		#ifdef RAINBOW
			hue++;
			hue %= 360;
		#endif
	}
}

