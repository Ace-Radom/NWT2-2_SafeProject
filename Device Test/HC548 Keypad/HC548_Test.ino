#include<Keypad.h>

const byte _ROWS = 3;
const byte _COLS = 4;

const char _Keymap[_ROWS][_COLS] = {
    { '#' , '9' , '6' , '3' },
    { '0' , '8' , '5' , '2' },
    { '*' , '7' , '4' , '1' }
};

const byte _rPIN[_ROWS] = { 13 , 12 , 11 };
const byte _cPIN[_COLS] = { 10 , 9 , 8 , 7 };

Keypad Safe_Keypad( makeKeymap( _Keymap ) , _rPIN , _cPIN , _ROWS , _COLS );

void setup(){
    Serial.begin( 9600 );
}

void loop(){
    char keypressed = Safe_Keypad.getKey();
    if ( keypressed != NO_KEY )
    {
        Serial.print(keypressed);
    }
}