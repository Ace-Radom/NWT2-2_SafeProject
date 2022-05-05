#include<TM74HC595_Driver.h>

TM74HC595 Display( 9 , 10 , 11 );

void setup(){
}

void loop(){
    Display.send( Display.Character_Point( '5' ) , 1 );
    delay( 1000 );
    Display.send( Display.Character_Point( '7' ) , 2 , _With_decimalPoint );
    delay( 1000 );
    Display.continuesend( Display.Character_Point( '6' ) , 3 , 500 );
    Display.continuesend( Display.Character_Point( '8' ) , 4 , _With_decimalPoint , 500 );
    Display.continuesend( "7890" , 500 );
    bool b[] = { true , false , true , false };
    Display.continuesend( "3579" , b , 500 );
    Display.clear();
    delay( 1000 );
    Display.send( Display.Character_Point( '-' ) , 1 );
    delay( 250 );
    Display.continuesend( "--  " , 250 );
    Display.continuesend( "--- " , 250 );
    Display.continuesend( "----" , 1250 );
}