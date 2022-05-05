#include<Safe_Class.h>
#include<TM74HC595_Driver.h>
//#include<Safe_Keypad.h>
#include<SoftwareSerial.h>
#include<Keypad.h>

TM74HC595 Display( 9 , 10 , 11 );

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
    
    /*
    Display.send( Display.Character_Point( '5' ) , 1 );
    delay( 1000 );
    Display.send( Display.Character_Point( '7' ) , 2 , _With_decimalPoint );
    delay( 1000 );
    Display.continuesend( Display.Character_Point( '6' ) , 3 , 500 );
    Display.continuesend( Display.Character_Point( '8' ) , 4 , _With_decimalPoint , 500 );
    Display.continuesend( "7890" , 500 );
    bool b[] = { true , false , true , false };
    Display.continuesend( "3579" , b , 500 );
    */
}