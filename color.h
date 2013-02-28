#ifndef COLOR_H
#define COLOR_H

typedef struct
{
	uint8_t red;
	uint8_t grn;
	uint8_t blu;
} color_t;

uint8_t _DDRD, _DDRC, _DDRB;
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

#endif
