//FONT MAPS
#ifndef FONTS_H
#define FONTS_h
//font maps stored in flash
//Note that the commented out line of _a is functionally identical to the uncommented line of _a
//The character is entered in binary and is rotated 90 degrees to the right
//These fonts were made manually and took about 4 hours total to create...

prog_uint8_t _a [] PROGMEM = {252, 19, 17, 19, 252};
/*prog_uint8_t _a [] PROGMEM = {B11111100,
                             B00010011,
                             B00010001,
                             B00010011,
                             B11111100 };*/
prog_uint8_t _b [] PROGMEM = {255, 145, 145, 145, 110};
prog_uint8_t _c [] PROGMEM = {126, 129, 129, 129, 102};
prog_uint8_t _d [] PROGMEM = {255, 129, 129, 66, 60};
prog_uint8_t _e [] PROGMEM = {255, 145, 145, 145, 129};
prog_uint8_t _f [] PROGMEM = {255, 17, 17, 17, 1};
prog_uint8_t _g [] PROGMEM = {126, 129, 145, 145, 246};
prog_uint8_t _h [] PROGMEM = {255, 16, 16, 16, 255};
prog_uint8_t _i [] PROGMEM = {129, 129, 255, 129, 129};
prog_uint8_t _j [] PROGMEM = {97, 129, 129, 127, 1};
prog_uint8_t _k [] PROGMEM = {255, 24, 36, 66, 129};
prog_uint8_t _l [] PROGMEM = {255, 128, 128, 128, 128};
prog_uint8_t _m [] PROGMEM = {255, 6, 24, 6, 255};
prog_uint8_t _n [] PROGMEM = {255, 6, 24, 96, 255};
prog_uint8_t _o [] PROGMEM = {126, 129, 129, 129, 126};
prog_uint8_t _p [] PROGMEM = {255, 17, 17, 17, 14};
prog_uint8_t _q [] PROGMEM = {62, 65, 65, 97, 190};
prog_uint8_t _r [] PROGMEM = {255, 17, 49, 81, 142};
prog_uint8_t _s [] PROGMEM = {78, 145, 145, 145, 102};
prog_uint8_t _t [] PROGMEM = {1, 1, 255, 1, 1};
prog_uint8_t _u [] PROGMEM = {127, 128, 128, 128, 127};
prog_uint8_t _v [] PROGMEM = {15, 48, 192, 48, 31};
prog_uint8_t _w [] PROGMEM = {63, 192, 48, 192, 63};
prog_uint8_t _x [] PROGMEM = {195, 36, 24, 36, 195};
prog_uint8_t _y [] PROGMEM = {3, 12, 240, 12, 3};
prog_uint8_t _z [] PROGMEM = {193, 161, 153, 133, 131};
prog_uint8_t _0 [] PROGMEM = {0, 126, 129, 126, 0};
prog_uint8_t _1 [] PROGMEM = {128, 130, 255, 128, 128};
prog_uint8_t _2 [] PROGMEM = {198, 161, 153, 133, 130};
prog_uint8_t _3 [] PROGMEM = {66, 145, 145, 145, 110};
prog_uint8_t _4 [] PROGMEM = {24, 20, 18, 255, 16};
prog_uint8_t _5 [] PROGMEM = {95, 145, 145, 145, 97};
prog_uint8_t _6 [] PROGMEM = {254, 145, 145, 145, 246};
prog_uint8_t _7 [] PROGMEM = {3, 1, 249, 5, 3};
prog_uint8_t _8 [] PROGMEM = {102, 153, 153, 153, 102};
prog_uint8_t _9 [] PROGMEM = {78, 145, 145, 145, 126};
prog_uint8_t _ast [] PROGMEM = {4, 10, 21, 10, 4};
prog_uint8_t _dol [] PROGMEM = {44, 74, 255, 82, 52};
prog_uint8_t _per [] PROGMEM = {192, 50, 24, 76, 3};
prog_uint8_t _exc [] PROGMEM = {0, 6, 191, 6, 0};
prog_uint8_t _til [] PROGMEM = {8, 4, 8, 16, 8};
prog_uint8_t _hsh [] PROGMEM = {36, 126, 36, 126, 36};
prog_uint8_t _crt [] PROGMEM = {0, 2, 1, 2, 0};
prog_uint8_t _opr [] PROGMEM = {129, 129, 66, 66, 60};
prog_uint8_t _cpr [] PROGMEM = {60, 66, 66, 129, 129};
prog_uint8_t _pls [] PROGMEM = {0, 8, 28, 8, 0};
prog_uint8_t _que [] PROGMEM = {6, 1, 177, 9, 6};
prog_uint8_t _equ [] PROGMEM = {0, 40, 40, 40, 0};
prog_uint8_t _min [] PROGMEM = {0, 16, 16, 16, 0};
prog_uint8_t _und [] PROGMEM = {128, 128, 128, 128, 128};
prog_uint8_t _com [] PROGMEM = {0, 128, 192, 0, 0};
prog_uint8_t _col [] PROGMEM = {0, 195, 195, 0, 0};
prog_uint8_t _scl [] PROGMEM = {0, 131, 195, 0, 0};
prog_uint8_t _apo [] PROGMEM = {0, 0, 3, 0, 0};
prog_uint8_t _obr [] PROGMEM = {255, 129, 129, 0, 0};
prog_uint8_t _cbr [] PROGMEM = {0, 0, 129, 129, 255};
prog_uint8_t _fsl [] PROGMEM = {192, 48, 24, 12, 3};
prog_uint8_t _bsl [] PROGMEM = {3, 12, 24, 48, 192};
prog_uint8_t _pip [] PROGMEM = {0, 0, 255, 0, 0};
prog_uint8_t _lth [] PROGMEM = {16, 40, 68, 130, 130};
prog_uint8_t _gth [] PROGMEM = {130, 130, 68, 40, 16};
prog_uint8_t _quo [] PROGMEM = {0, 3, 0, 3, 0};
prog_uint8_t _oba [] PROGMEM = {16, 126, 129, 129, 0};
prog_uint8_t _cba [] PROGMEM = {0, 129, 129, 126, 16};
prog_uint8_t _prd [] PROGMEM = {0, 32, 112, 32, 0};
prog_uint8_t _spa [] PROGMEM = {0, 0, 0, 0, 0};
prog_uint8_t _tck [] PROGMEM = {0, 1, 3, 0, 0};
prog_uint8_t _at  [] PROGMEM = {122, 133, 129, 126};
prog_uint8_t _amp [] PROGMEM = {118, 137, 118, 6, 9};

uint8_t *charSet[] =
{
 _spa,//0
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,//9
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,//19
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,
 _spa,//29
 _spa,
 _spa,

 _spa,
 _exc,
 _quo,
 _hsh,
 _dol,
 _per,
 _spa, //amp
 _apo,//39
 _opr,
 _cpr,
 _ast,
 _pls,
 _com,
 _min,
 _prd,
 _fsl,

 _0,
 _1,//49
 _2,
 _3,
 _4,
 _5,
 _6,
 _7,
 _8,
 _9,

 _col,
 _scl,//59
 _lth,
 _equ,
 _gth,
 _que,
 _at,

 _a,
 _b,
 _c,
 _d,
 _e,//69
 _f,
 _g,
 _h,
 _i,
 _j,
 _k,
 _l,
 _m,
 _n,
 _o,//79
 _p,
 _q,
 _r,
 _s,
 _t,
 _u,
 _v,
 _w,
 _x,
 _y,//89
 _z,

 _oba,
 _bsl,
 _cba,
 _crt,
 _und,

 _til,
 _a,
 _b,
 _c,//99
 _d,
 _e,
 _f,
 _g,
 _h,
 _i,
 _j,
 _k,
 _l,
 _m,//109
 _n,
 _o,
 _p,
 _q,
 _r,
 _s,
 _t,
 _u,
 _v,
 _w,//119
 _x,
 _y,
 _z,

 _oba,
 _pip,
 _cba,
 _til,
 _spa
};


#endif
