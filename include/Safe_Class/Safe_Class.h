/*
 * 本头文件在项目文件夹下编辑
 * 并在完成编辑后复制至C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\Safe_Class下覆盖
 * 
 * 在本头文件中主要声明了在运行过程中保险箱所需要的所有函数和数据寄存器
 * 包括：
 * * 各个设备与Arduino主板通信的接口
 * * 密码数据
 * * 实现保险箱工作所需要的各项功能的函数
 * * 保险箱功能实现所需要的部分头文件和define声明
 * 但不包括：
 * * HC-06蓝牙核心模块软串口声明及使用
 * * TM74HC595数字显示模块声明及使用
 * * 串口声明
 * * 串口输入输出
 * 在头文件完成并覆盖入Arduino自定义库文件夹后 需在项目文件夹下 $\main.ino下引用
*/

#ifndef _SAFE_CLASS_H_
#define _SAFE_CLASS_H_

#include<Arduino.h>

class Safe_Class{
    public:
        //构造函数 (设定所有设备的通信接口和程序内参数)
        Safe_Class( uint16_t _StepMotor_1 , uint16_t _StepMotor_2 , uint16_t _StepMotor_3 , uint16_t _StepMotor_4 , uint64_t _StepMotor_SPR_Set , uint16_t _Stepmotor_Speed_Set );

        //向计算机终端发送验证码
        void send_Verification_Code();

        //验证在密码盘上输入的验证码是否正确
        bool Admin_Verify( long _Verification_Code_INPUT );

    private:
        //程序运行参数
        uint16_t _Speaker_PIN;  /* 扬声器通信接口 */

        uint16_t _StepMotor_PIN1;  /* 步进式马达IN1 (R1) */
        uint16_t _StepMotor_PIN2;  /* 步进式马达IN2 (R2) */
        uint16_t _StepMotor_PIN3;  /* 步进式马达IN3 (R3) */
        uint16_t _StepMotor_PIN4;  /* 步进式马达IN4 (R4) */
        uint16_t _StepMotor_Speed;  /* 步进式马达每分钟旋转圈数 */
        uint64_t _StepMotor_SPR;  /* 步进式马达每圈分步数量 SPR = Step per Rotation */

        uint64_t _StepMotor_LBS;  /* 步进式马达每步间间隔 (ms) LBS = Latency between Steps */
        uint16_t _StepMotor_Direction = 0;  /* 步进式马达旋转方向 */
        uint16_t _StepMotor_StepNUM;  /* 步进式马达启动接口 */
        uint64_t _StepMotor_LST;  /* 步进式马达上次步进时间 LST = Last Step's Time */

        //步进式马达参数预设
        void _StepMotor_Preset();

        //步进式马达旋转 (调用接口)
        void _StepMotor_Step( uint32_t _stepNUM );

        //步进式马达旋转 (工作接口)
        void _StepMotor( uint32_t _this_Step );

        //验证码生成器
        void _Verification_Code_Create();

        //密码寄存器
        long _Password;

        //验证码寄存器
        long _Verification_Code;
};

#endif