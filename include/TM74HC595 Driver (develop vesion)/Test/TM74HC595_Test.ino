#include<TM74HC595_Driver.h>

TM74HC595 Display( 9 , 10 , 11 );

void setup(){
}

void loop(){
    Display.send( 0x60 , 1 );
    Display.send( Display.Character_Point( '2' ) , 2 );
    Display.send( 0xF2 , 3 , _With_decimalPoint );
    Display.send( Display.Character_Point( '4' ) , 4 , _With_decimalPoint );
    Display.continuesend( 0x60 , 1 , 500 );
    Display.continuesend( Display.Character_Point( '2' ) , 2 , _With_decimalPoint , 500 );
    Display.continuesend( "1234" , 500 );
    bool b[] = { true , false , true , false };
    Display.continuesend( "5678" , b , 500 );
}

