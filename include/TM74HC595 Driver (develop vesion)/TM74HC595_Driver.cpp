#include<TM74HC595_Driver.h>
#include<Arduino.h>

_Display_Preset _LED_Preset[] = {
    { '0' , 0xFC },     /* BIN: 1111 1100 */
    { '1' , 0x60 },     /* BIN: 0110 0000 */
    { '2' , 0xDA },     /* BIN: 1101 1010 */
    { '3' , 0xF2 },     /* BIN: 1111 0010 */
    { '4' , 0x66 },     /* BIN: 0110 0110 */
    { '5' , 0xB6 },     /* BIN: 1011 0110 */
    { '6' , 0xBE },     /* BIN: 1011 1110 */
    { '7' , 0xE0 },     /* BIN: 1110 0000 */
    { '8' , 0xFE },     /* BIN: 1111 1110 */
    { '9' , 0xF6 },     /* BIN: 1111 0110 */
    { '-' , 0x02 },     /* BIN: 0000 0010 */
    { ' ' , 0x00 }      /* BIN: 0000 0000 */
};

/*
 * 在一个数字显示器内：
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
 * 每一LED的开关设定【1和0】按照上图顺序连接 并在第八位补上0 组成一个二进制数并送入模块 便可以控制每一位上的七个LED
*/

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
    return;
}

void TM74HC595::send( unsigned int _INPUT , unsigned short int _port ){
    setDigit( _INPUT , _port , false );
    return;
}

void TM74HC595::send( unsigned int _INPUT , unsigned short int _port , bool _decimalPoint ){
    setDigit( _INPUT , _port , _decimalPoint );
}

void TM74HC595::continuesend( unsigned int _INPUT , unsigned short int _port , long long _continueTime ){
    long long _startTime = millis();
    long long _nowTime = millis();
    while ( _nowTime - _startTime < _continueTime )
    {
        _nowTime = millis();
        setDigit( _INPUT , _port , false );
    }
    //判断已持续时间是否超过持续时长
    return;
}

void TM74HC595::continuesend( unsigned int _INPUT , unsigned short int _port , bool _decimalPoint , long long _continueTime ){
    long long _startTime = millis();
    long long _nowTime = millis();
    while ( _nowTime - _startTime < _continueTime )
    {
        _nowTime = millis();
        setDigit( _INPUT , _port , _decimalPoint );
    }
    //判断已持续时间是否超过持续时长
    return;
}


void TM74HC595::continuesend( char _INPUT[] , long long _continueTime ){
    long long _startTime = millis();
    long long _nowTime = millis();
    while ( _nowTime - _startTime < _continueTime )
    {
        _nowTime = millis();
        for ( int i = 0 ; i < 4 ; i++ )
        {
            if ( _INPUT[i] != ' ' )
            {
                setDigit( Character_Point( _INPUT[i] ) , i + 1 , false );
            }
            //若该位为空则不做输出
        }
    }
    //判断已持续时间是否超过持续时长
    return;
}

void TM74HC595::continuesend( char _INPUT[] , bool _decimalPoint[] , long long _continueTime ){
    long long _startTime = millis();
    long long _nowTime = millis();
    while ( _nowTime - _startTime < _continueTime )
    {
        _nowTime = millis();
        for ( int i = 0 ; i < 4 ; i++ )
        {
            if ( _INPUT[i] != ' ' )
            {
                setDigit( Character_Point( _INPUT[i] ) , i + 1 , _decimalPoint[i] );
                //在末尾设置该位后是否输出小数点
            }
            //若该位为空则不做输出
        }
    }
    //判断已持续时间是否超过持续时长
    return;
}


void TM74HC595::clear(){
    setDigit( 0x00 , 1 , false );
    setDigit( 0x00 , 2 , false );
    setDigit( 0x00 , 3 , false );
    setDigit( 0x00 , 4 , false );
    return;
}

unsigned int TM74HC595::Character_Point( char _INPUT ){
    for ( int i = 0 ; i < _Preset_Array_Length_ ; i++ )
    {
        if ( _LED_Preset[i]._Character == _INPUT )
        {
            return _LED_Preset[i]._NUM;
        }
    }
    return 0x00;
}

//私有成员函数部分

void TM74HC595::setDigit( int _OUTPUT , unsigned short int _port , bool _decimalPoint ){
    unsigned int _rowSelector;
    unsigned int _data;
    _rowSelector = bit ( 4 - _port ) << 4;
    _data = ~ _OUTPUT;
    if ( _decimalPoint )
    {
        _data &= 0xFE;
    }
    //判断是否显示小数点
    shiftOut( _DIO_PIN , _SCLK_PIN , LSBFIRST , _data );
    digitalWrite( _RCLK_PIN , LOW );
    shiftOut( _DIO_PIN , _SCLK_PIN , LSBFIRST , _rowSelector );
    digitalWrite( _RCLK_PIN , HIGH );
    return;
}