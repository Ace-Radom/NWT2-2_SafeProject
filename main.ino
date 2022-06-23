#include<Safe_Class.h>
#include<TM74HC595_Driver.h>
//#include<Safe_Keypad.h>
#include<SoftwareSerial.h>
#include<Keypad.h>
#include<Stepper.h>
#include<Stepper_28BYJ48.h>

/* ========================================= Definition ========================================= */

#define LED_RED PIN_A5
#define LED_GREEN PIN_A4
#define SCLK 9
#define RCLK 10
#define DIO 11
#define Motor1 PIN_A3
#define Motor2 PIN_A1
#define Motor3 PIN_A2
#define Motor4 PIN_A0
#define Speaker 12

#define DisplayTurn( x ) ( 5 - x )
//TM74HC595 fangt von rechts an

#define StepMotorSPR 2048
#define StepperTurnSteps 2048

#define SpeakerFrequency_PasswordRight 1000
#define SpeakerFrequency_PasswordWrong 500

/* ========================================= VAR Preset ========================================= */

uint16_t password;
uint16_t password_temp;
bool password_set;

bool Dooropen;

/* ========================================= TM74HC595 ========================================= */

TM74HC595 Display( SCLK , RCLK , DIO );
char display_num[5];
uint8_t digit;
//Das Nummer auf das Displaymodule, wenn man die Tastern druckt, das wird verändern

/* ========================================= 28BYJ48 ========================================= */

Stepper_28BYJ48 Stepmotor( StepMotorSPR , Motor1 , Motor3 , Motor2 , Motor4 );

/* ========================================= Keypad ========================================= */

const byte _ROWS = 4;
const byte _COLS = 3;

const char _Keymap[_ROWS][_COLS] = {
    { '1' , '2' , '3' },    
    { '4' , '5' , '6' },    
    { '7' , '8' , '9' },   
    { '*' , '0' , '#' }
};

const byte _rPIN[_ROWS] = { 2 , 3 , 4 , 5 };
const byte _cPIN[_COLS] = { 6 , 7 , 8 };

Keypad Safe_Keypad( makeKeymap( _Keymap ) , _rPIN , _cPIN , _ROWS , _COLS );

/* ========================================= Function DEF ========================================= */

void displayreset();

void screendisplay();
void readpassword( uint16_t &address );

void password_right();
void password_wrong();

void dooropen();
void doorclose();

/* ========================================= Main Program ========================================= */

void setup(){
    displayreset();
    Display.clear();
    password = 0;
    password_temp = 0;
    password_set = false;
    Stepmotor.setSpeed( 10 );
    pinMode( LED_GREEN , OUTPUT );
    pinMode( LED_RED , OUTPUT );
    Dooropen = true;
    Serial.begin( 9600 );
}

void loop(){
    screendisplay();
    char keypressed = Safe_Keypad.getKey();
    if ( keypressed != NO_KEY )
    {
        Serial.println( keypressed );
        if ( keypressed == '#' && digit != 1 )
        {
            displayreset();
            Display.clear();
        }
        else
        {
            if ( keypressed == '#' && Dooropen && digit == 1 )
            {
                password = 0;
                password_set = false;
            }
        }
        if ( keypressed != '*' && keypressed != '#' )  //Man hat Zahl eingegeben
        {
            if ( digit != 5 )
            {
                display_num[digit] = keypressed;
                digit++;
            }
            //Wenn digit gleich wie 4 ist, man kann nicht mehr Zahle eingeben
        }
        if ( keypressed == '*' && digit == 5 )
        {
            if ( !password_set )
            {
                readpassword( password );
                password_set = true;
                doorclose();
                Display.clear();
            }
            else
            {
                readpassword( password_temp );
                if ( password_temp == password )
                {
                    password_right();
                    Display.clear();
                    password_temp = 0;
                }
                else
                {
                    password_wrong();
                    Display.clear();
                    password_temp = 0;
                }
            }
        }
        if ( keypressed == '*' && digit == 1 && Dooropen )
        {
            doorclose();
        }
        delay( 100 );
        //Warten bis die Hände die Tastatur verlassen
    }
}

/* ========================================= Function Main ========================================= */

/* Setz TM74HC595 zurück */
void displayreset(){
    memset( display_num , ' ' , sizeof( display_num ) );
    digit = 1;
    return;
}

/* Display Funktion */
void screendisplay(){
    Display.send( Display.Character_Point( display_num[1] ) , DisplayTurn( 1 ) );
    Display.send( Display.Character_Point( display_num[2] ) , DisplayTurn( 2 ) );
    Display.send( Display.Character_Point( display_num[3] ) , DisplayTurn( 3 ) );
    Display.send( Display.Character_Point( display_num[4] ) , DisplayTurn( 4 ) );
    return;
}

/* Tausch Kennenwort von char zu int */
void readpassword( uint16_t &address ){
    for ( int i = 1 ; i <= 4 ; i++ )
    {
        password *= 10;
        password += ( int ) display_num[i] - 30;
        //Im ACSII '0' hat ein Nummer 30
    }
    return;
}

void password_right(){
    digitalWrite( LED_GREEN , HIGH );
    tone( Speaker , SpeakerFrequency_PasswordRight );
    dooropen();
    noTone( Speaker );
    digitalWrite( LED_RED , LOW );
    return;
}

void password_wrong(){
    digitalWrite( LED_RED , HIGH );
    tone( Speaker , SpeakerFrequency_PasswordWrong );
    noTone( Speaker );
    digitalWrite( LED_RED , LOW );
    return;
}

void dooropen(){
    Stepmotor.step( StepperTurnSteps );
    Dooropen = true;
    return;
}

void doorclose(){
    Stepmotor.step( -StepperTurnSteps );
    Dooropen = false;
    return;
}