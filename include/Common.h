#ifndef COMMON_H
#define COMMON_H

namespace YJI
{
class Common
{
public:
    // 导航电脑传过来的数据
    enum UDPMessage : unsigned char
    {
        Invalid = 0,
        Linear,
        Angular,
        Charger_Switch,
        Final_Pose,
        Power_State,
        Button_Stop,
        Charge_State,
        Motor_Lock_State,
        Position,
        Rotation,
        Twist,
        Percent,
        Voltage,
        Current
    };

    // AGV位置信息
    struct AGVPos
    {
        float AGVX;
        float AGVY;
        float AGVYaw;
    };

    // 小车速度
    struct AGVVel
    {
        float Linear;
        float Angular;
    };

    // 底盘小车数据回传
    struct AGVInfo
    {
        int Vx;
        float Vz;
        float AccX;
        float AccY;
        float AccZ;
        float GyrX;
        float GyrY;
        float GyrZ;
        int16_t Voltage;
        int16_t State;
        int16_t Light12;
        int16_t Light34;
    };
};

// 底盘回传的AGV信息
extern Common::AGVInfo AGV_Info;

extern Common::AGVPos AGV_Pos;

extern Common::AGVVel AGV_Vel;

extern bool Charger_Switch;

}


#endif