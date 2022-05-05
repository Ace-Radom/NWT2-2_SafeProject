#include"Safe_Class.h"

//公有成员函数部分

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

//私有成员函数部分

void Safe_Class::_Verification_Code_Create(){
    _Verification_Code = random( 1000 , 9999 );
}