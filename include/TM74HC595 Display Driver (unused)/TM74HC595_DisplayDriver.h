#ifndef _TM74HC595_DISPLAYDRIVER_H_
#define _TM74HC595_DISPLAYDRIVER_H_

#define _WITHZERO true
#define _WITHOUTZERO false
#define _PRIVATE_SIGN true

struct _Display_Set{
    char _Character;
    unsigned char _NUM;
};

class TM74HC595{
    public:
        //构造函数
        TM74HC595( int _SCLK , int _RCLK , int _DIO );

        //向指定位送入字符数据【指定位可为多个】
        void send( unsigned char _INPUT , unsigned char _port );

        //向模块送入字符串【长度固定为4】
        //void send( String _INPUT ); 

        //以指定位起始送入两位整数【未满两位以0补齐】
        void digit2( int _INPUT , unsigned char _port );

        //向模块送入四位整数【未满四位则空出】
        void digit4( int _INPUT );

        //向模块送入四位整数【未满四位则以零补齐】
        void digit4_showZero( int _INPUT );

        //输入字符与显示参数指示器
        unsigned char Character_Point( char _INPUT );

    private:
        int _SCLK_PIN;
        int _RCLK_PIN;
        int _DIO_PIN;

        //向模块送入字符数据
        void send( unsigned char _OUTPUT );

        //void send( String _OUTPUT ,bool _Private_SIGN );

        //向模块送入两位整数
        void digit2( int _OUTPUT , unsigned char _port , bool _Private_SIGN );

        //向模块送入四位整数
        void digit4( int _OUTPUT , bool _showZero );
};

#endif