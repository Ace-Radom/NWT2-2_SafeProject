#ifndef _SAFE_KEYPAD_H_
#define _SAFE_KEYPAD_H_

#include<Keypad.h>

const byte _ROWS = 4;
const byte _COLS = 3;

const char _Keymap[_ROWS][_COLS] = {
    { '1' , '2' , '3' },
    { '4' , '5' , '6' },
    { '7' , '8' , '9' },
    { '*' , '0' , '#' }
};

const byte _rPIN[_ROWS] = { 10 , 9 , 8 , 7 };
const byte _cPIN[_COLS] = { 6 , 5 , 4 };

Keypad Safe_Keypad( makeKeymap( _Keymap ) , _rPIN , _cPIN , _ROWS , _COLS );

#endif