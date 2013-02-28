#ifndef PWM_H
#define PWM_H

const uint8_t dptt []  = {0,0,0,7,0,2,1,0,0,3,4,6,0,0,0,0,0,0,0}; //map output pin to timer

void aWrite(uint8_t pin, unsigned int val)
{
        switch(dptt[pin])
        {
                case 1:
                        // connect pwm to pin on timer 0, channel A
                        OCR0A = val; // set pwm duty
                        break;
                case 2:
                        // connect pwm to pin on timer 0, channel B
                        OCR0B = val; // set pwm duty
                        break;
                case 3:
                        // connect pwm to pin on timer 1, channel A
                        OCR1A = val; // set pwm duty
                        break;
                case 4:
                        // connect pwm to pin on timer 1, channel B
                        OCR1B = val; // set pwm duty
                        break;
                case 6:
                        // connect pwm to pin on timer 2, channel A
                        OCR2A = val; // set pwm duty
                        break;
                case 7:
                        // connect pwm to pin on timer 2, channel B
                        OCR2B = val; // set pwm duty
                        break;
        }
}

#endif
