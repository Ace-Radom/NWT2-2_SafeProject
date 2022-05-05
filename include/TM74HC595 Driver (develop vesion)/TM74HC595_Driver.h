#ifndef _TM74HC595_DRIVER_H_
#define _TH74HC595_DRIVER_H_

using namespace std;

#define _Preset_Array_Length_ 12

#define _With_decimalPoint true
#define _without_decimalPoint false

struct _Display_Preset
{
    char _Character;
    int _NUM;
};

class TM74HC595{
    public:
        //构造函数
        TM74HC595( int _SCLK , int _RCLK , int _DIO );

        //向指定位送入字符数据
        void send( unsigned int _INPUT , unsigned short int _port );

        //向指定位送入字符数据【可选择小数点】
        void send( unsigned int _INPUT , unsigned short int _port , bool _decimalPoint );

        //持续n微秒向指定位送入字符数据
        void continuesend( unsigned int _INPUT , unsigned short int _port , long long _continueTime );

        //持续n微秒向指定位送入字符数据【可选择小数点】
        void continuesend( unsigned int _INPUT , unsigned short int _port , bool _decimalPoint , long long _continueTime );

        //持续n微秒向模块送入数据【字符数组_INPUT应为四位模块可显示的字符】
        void continuesend( char _INPUT[] , long long _continueTime );

        //持续n微秒向模块送入数据【字符数组_INPUT应为四位模块可显示的字符 _decimalPoint[]应为四位布尔型 记录每一小数点的开关（开以true表示）】
        void continuesend( char _INPUT[] , bool _decimalPoint[] , long long _continueTime );

        //清除模块内显示的数据
        void clear();

        //显示参数指示器
        unsigned int Character_Point( char _INPUT );

    private:
        int _SCLK_PIN;
        int _RCLK_PIN;
        int _DIO_PIN;

        //显示模块控制
        void setDigit( int _OUTPUT , unsigned short int _port , bool _decimalPoint );
};

#endif