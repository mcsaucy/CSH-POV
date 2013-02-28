#ifndef FLUSH_H
#define FLUSH_H

//read in from serial and do nothing with the result
void flush(void)
{
	register uint8_t null;
	while  (UCSR0A & (1<<RXC0)) 
	{
		null = UDR0;
	}
}

#endif
