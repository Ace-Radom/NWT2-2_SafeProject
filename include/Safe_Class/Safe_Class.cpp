#include<Safe_Class.h>

//公有成员函数部分

Safe_Class::Safe_Class( uint16_t _StepMotor_1 , uint16_t _StepMotor_2 , uint16_t _StepMotor_3 , uint16_t _StepMotor_4 , uint64_t _StepMotor_SPR_Set , uint16_t _StepMotor_Speed_Set ){
    _StepMotor_PIN1 = _StepMotor_1;
    _StepMotor_PIN2 = _StepMotor_2;
    _StepMotor_PIN3 = _StepMotor_3;
    _StepMotor_PIN4 = _StepMotor_4;
    _StepMotor_SPR = _StepMotor_SPR_Set;
    _StepMotor_Speed = _StepMotor_Speed_Set;
    _StepMotor_Preset();
}

void Safe_Class::send_Verification_Code(){
    _Verification_Code_Create();
    Serial.begin( 9600 );
    Serial.print( "Your Verification Code is:" );
    Serial.println( _Verification_Code );
    Serial.end();
}

bool Safe_Class::Admin_Verify( long _Verification_Code_INPUT ){
    if ( _Verification_Code_INPUT == _Verification_Code )
    {
        return true;
    }
    return false;
}

void Safe_Class::_StepMotor_TestFunction( uint32_t _Step ){
    _StepMotor_Step( _Step );
}

//私有成员函数部分

void Safe_Class::_Verification_Code_Create(){
    _Verification_Code = random( 1000 , 9999 );
}

void Safe_Class::_StepMotor_Preset(){
    _StepMotor_StepNUM = 0;
    _StepMotor_Direction = 0;
    _StepMotor_LST = 0;
    pinMode( _StepMotor_PIN1 , OUTPUT );
    pinMode( _StepMotor_PIN2 , OUTPUT );
    pinMode( _StepMotor_PIN3 , OUTPUT );
    pinMode( _StepMotor_PIN4 , OUTPUT );
    _StepMotor_LBS = 60L * 1000L * 1000L / _StepMotor_SPR / _StepMotor_Speed;
}

void Safe_Class::_StepMotor_Step( uint32_t _stepNUM ){
    long _steps_LEFT = abs( _stepNUM );
    if ( _stepNUM > 0 )
    {
        _StepMotor_Direction = 1;
    }
    if ( _stepNUM < 0 )
    {
        _StepMotor_Direction = 0;
    }
    while ( _steps_LEFT > 0 )
    {
        uint64_t _NOW = micros();
        if ( _NOW - _StepMotor_LST >= _StepMotor_LBS )
        {
            _StepMotor_LST = _NOW;
            if ( _StepMotor_Direction == 1 )
            {
                _StepMotor_StepNUM++;
                if ( _StepMotor_StepNUM == _StepMotor_SPR )
                {
                    _StepMotor_StepNUM = 0;
                }
            }
            else
            {
                if ( _StepMotor_StepNUM == 0 )
                {
                    _StepMotor_StepNUM = _StepMotor_SPR;
                }
                _StepMotor_StepNUM--;
            }
            _steps_LEFT--;
            _StepMotor( _StepMotor_StepNUM % 4 );
        }
    }
}

void Safe_Class::_StepMotor( uint32_t _this_Step ){
    switch ( _this_Step ){
        case 0:
            digitalWrite( _StepMotor_PIN1 , HIGH );
            digitalWrite( _StepMotor_PIN2 , LOW );
            digitalWrite( _StepMotor_PIN3 , HIGH );
            digitalWrite( _StepMotor_PIN4 , LOW );
            break;
    
        case 1:
            digitalWrite( _StepMotor_PIN1 , LOW );
            digitalWrite( _StepMotor_PIN2 , HIGH );
            digitalWrite( _StepMotor_PIN3 , HIGH );
            digitalWrite( _StepMotor_PIN4 , LOW );
            break;
        
        case 2:
            digitalWrite( _StepMotor_PIN1 , LOW );
            digitalWrite( _StepMotor_PIN2 , HIGH );
            digitalWrite( _StepMotor_PIN3 , LOW );
            digitalWrite( _StepMotor_PIN4 , HIGH );
            break;

        case 3:
            digitalWrite( _StepMotor_PIN1 , HIGH );
            digitalWrite( _StepMotor_PIN2 , LOW );
            digitalWrite( _StepMotor_PIN3 , LOW );
            digitalWrite( _StepMotor_PIN4 , HIGH );
            break;
    }
}