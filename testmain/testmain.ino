#include<Safe_Class.h>
#include<TM74HC595_Driver.h>
#include<SoftwareSerial.h>
#include<Keypad.h>
#include<Stepper_28BYJ48.h>

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

#define inside( x , y , z ) ( x >= y && x <= z )

#define StepMotorSPR 2048
#define StepperTurnSteps 2048

uint16_t readin;

uint16_t password;
uint16_t password_temp;
bool password_set = false;

bool Dooropen = true;

TM74HC595 Display( SCLK , RCLK , DIO );
char display_num[5];
uint8_t digit;

Stepper_28BYJ48 Stepmotor( StepMotorSPR , Motor1 , Motor3 , Motor2 , Motor4 );

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

void setup(){
    readin = 0;
}

void loop(){
    char keypressed = Safe_Keypad.getKey();
    if ( keypressed != NO_KEY )
    {
        Serial.println( keypressed );
        if ( keypressed != '#' && keypressed != '*' )
        {
            readin *= 10;
            readin += ( int ) keypressed - 30;
        }
        else
        {
            switch ( keypressed ){
                case '#':
                    if ( inside( readin , 1000 , 9999 ) )
                    {
                        Serial.println( "readin data inside" );
                        if ( Dooropen )
                        {
                            password = readin;
                            Dooropen = false;
                            readin = 0;
                            Serial.println( "door closed" );
                        }
                        else
                        {
                            if ( readin = password )
                            {
                                password = 0;
                                Dooropen = true;
                                readin = 0;
                                Serial.println( "door open" );
                            }
                            else
                            {
                                readin = 0;
                                Serial.println( "wrong password" );
                            }
                        }
                    }
                    break;
            
                case '*':
                    readin = 0;
                    break;
            }
        }
    }
}