#include<TM74HC595_DisplayDriver.h>
#include<Arduino.h>

_Display_Set _LED_0F[] = {
    /* 记录各个可输出的字符在.send成员函数内的输出参数 */
    { '0' , 0xC0 },
    { '1' , 0xF9 },
    { '2' , 0xA4 },
    { '3' , 0xB0 },
    { '5' , 0x92 },
    { '6' , 0x82 },
    { '7' , 0xF8 },
    { '8' , 0x80 },
    { '9' , 0x90 },
    { 'A' , 0x88 },
    { 'b' , 0x83 },
    { 'C' , 0xC6 },
    { 'd' , 0xA1 },
    { 'E' , 0x86 },
    { 'F' , 0x8E },
    { 'G' , 0xC2 },
    { 'H' , 0x89 },
    { 'I' , 0xF9 },
    { 'J' , 0xF1 },
    { 'L' , 0xC3 },
    { 'n' , 0xA9 },
    { 'O' , 0xC0 },
    { 'P' , 0x8C },
    { 'q' , 0x98 },
    { 'S' , 0x92 },
    { 'U' , 0xC1 },
    { 'Y' , 0x91 },
    { '-' , 0xFE },
};

//公有成员函数部分

TM74HC595::TM74HC595( int _SCLK , int _RCLK , int _DIO ){
    _SCLK_PIN = _SCLK;
    _RCLK_PIN = _RCLK;
    _DIO_PIN = _DIO;
    //复制记录SCLK RCLK DIO连接接口
    pinMode( _SCLK_PIN , OUTPUT );
    pinMode( _RCLK_PIN , OUTPUT );
    pinMode( _DIO_PIN , OUTPUT );
    //将SCLK RCLK DIO三接口的连接方式设为输出
}

void TM74HC595::send( unsigned char _INPUT , unsigned char _port ){
    send( _INPUT );
    send( _port );
    digitalWrite( _RCLK_PIN , LOW );
    digitalWrite( _RCLK_PIN , HIGH );
}

void TM74HC595::digit2( int _INPUT , unsigned char _port ){
    digit2( _INPUT , _port , _PRIVATE_SIGN );
}

void TM74HC595::digit4( int _INPUT ){
    digit4( _INPUT , _WITHOUTZERO );
}

void TM74HC595::digit4_showZero( int _INPUT ){
    digit4( _INPUT , _WITHZERO );
}

unsigned char TM74HC595::Character_Point( char _INPUT ){
    for ( int i = 0 ; i < 29 ; i++ )
    {
        if ( _LED_0F[i]._Character == _INPUT )
        {
            return _LED_0F[i]._NUM;
        }
    }
}

//私有成员函数部分

void TM74HC595::send( unsigned char _OUTPUT ){
    for ( int i = 8 ; i >= 1 ; i-- )
    {
        if ( _OUTPUT & 0x80 )
        {
            digitalWrite( _DIO_PIN , HIGH );
        }
        else
        {
            digitalWrite( _DIO_PIN , LOW );
        }
        _OUTPUT <<= 1;
        digitalWrite( _SCLK_PIN , LOW );
        digitalWrite( _SCLK_PIN , HIGH );
    }
}

void TM74HC595::digit2( int _OUTPUT , unsigned char _port , bool _Private_SIGN ){
    int _OUTPUT1, _OUTPUT2;
    _OUTPUT1 = ( int ) _OUTPUT % 10;
    _OUTPUT2 = ( int ) _OUTPUT / 10 % 10;
    send( _LED_0F[_OUTPUT1]._NUM , _port );
    send( _LED_0F[_OUTPUT2]._NUM , _port << 1 );
}

void TM74HC595::digit4( int _OUTPUT , bool _showZero ){
    int _OUTPUT1, _OUTPUT2, _OUTPUT3, _OUTPUT4;
    _OUTPUT1 = ( int ) _OUTPUT % 10;
    _OUTPUT2 = ( int ) _OUTPUT / 10 % 10;
    _OUTPUT3 = ( int ) _OUTPUT / 100 % 10;
    _OUTPUT4 = ( int ) _OUTPUT / 1000;
    send( _LED_0F[_OUTPUT1]._NUM , 0b0001 );
    if ( _showZero | _OUTPUT > 9 )
    {
        send( _LED_0F[_OUTPUT2]._NUM , 0b0010 );        
    }
    if ( _showZero | _OUTPUT > 99 )
    {
        send( _LED_0F[_OUTPUT3]._NUM , 0b0100 );
    }
    if ( _showZero | _OUTPUT > 999 )
    {
        send( _LED_0F[_OUTPUT4]._NUM , 0b1000 );
    }
}