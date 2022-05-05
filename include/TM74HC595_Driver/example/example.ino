#include<TM74HC595_Driver.h>

#define SCLK 9
#define RCLK 10
#define DIO 11

TM74HC595 Display( SCLK , RCLK , DIO );

// set the three pins the TM74HC595 module needs: SCLK, RCLK, DIO as 9, 10, 11

void setup(){
}

// normally when you use this driver, you don't need to add anything into the setup function to set something up

/*
 * WARNING!!!
 * I don't know actually why but, every time you want to display A new character, the character you've in the last time displayed will be pumped out
 * That means, when you need to display a number like "123" or "1234", please use .send() with while or .continuesend()
*/

void loop(){
    Display.send( Display.Character_Point( '1' ) , 1 );
    // That means, display '1' on the first display block (from right to left)
    // .Character_Point() is written for simplifying the process of the display set, because normally you need to give the "Display Code" to make the module knows what you mean, and it's hard to learn and remember
    // There's a struct array in the library, and this function will automaticly search the character you've given in this array, and return the "Display Code" for this character when it finds

    Display.send( 0x60 , 2 );
    // Surely, you can also program in this way (it means display '1' on the second display block)

    /*
     * The reason why I don't directly use the type like ".send( '1' , 1 )" is, I want to make it possible to display something not a character at all on this module
     * This "Display Code", in fact, is a 8-bit binary number and always ends with 0. The first seven bits use 1 and 0 to set the seven LEDs in each display block as on and off in clockwise direction
     * Like this: (it shows the order of each LED in display blocks)
     *          1
     *       ═══════
     *      ║       ║
     *    6 ║       ║ 2
     *      ║   7   ║
     *       ═══════
     *      ║       ║
     *    5 ║       ║ 3
     *      ║       ║
     *       ═══════
     *          4
     * But to tell the truth, I recommend using the first way with .Character_Point() because it looks more intuitively
    */

    Display.send( Display.Character_Point( '2' ) , 3 , _With_decimalPoint );
    // This will turn the decimal point after the thrid display block on (_With_decimalPoint is linked to true) at the same time when it display '2' on the third block

    Display.continuesend( 0x60 , 1 , 500 );
    Display.continuesend( Display.Character_Point( '2' ) , 2 , _With_decimalPoint , 500 );
    Display.continuesend( "1234" , 500 );
    bool b[] = { true , false , true , false };
    Display.continuesend( "5678" , b , 500 );

    /*
     * These show how to use .continuesend()
     * So like these sentences, you can set not only one character, but also 4 in one time
     * The first and second sentences don't have something really 'new', you only need to set how long (ms) you want the character to display, others are all the same as normal .send()
     * The only two things I need to explain are in the third and fourth sentences: You always need to give a character array with four characters, otherwise it may go wrong
     * The four characters need to be in the order from the first block to the fourth (from right to left)
     * The fours shows how to turn on the decimal points. You need to give a boolean array always with four 'true / false', like the array b here. Sadly I don't have the ability to make it easier...
    */

    Display.clear();
    // It will clear all the characters in display

    delay( 1000 );
}