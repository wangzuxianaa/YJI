#ifndef COMMON_H
#define COMMON_H

class Common
{
public:
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
};

#endif