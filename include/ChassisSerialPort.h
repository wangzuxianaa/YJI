#ifndef CHASSISSERIALPORT_H
#define CHASSISSERIALPORT_H

#include <boost/asio.hpp>

typedef unsigned char      u8;
typedef unsigned short int u16;
typedef short int          s16;
typedef int                s32;

namespace YJI
{

class System;
class UDPServer;

class ChassisSerialPort
{
public:
    // 轴距
    static constexpr int BaseWidth = 348;

    // 数据头
    static constexpr uint32_t HEADER = 0xDEED;

    //打开20ms数据上传结构体
    union OPen20MsData
    {
    u8 data[10];
    struct
    {
        u16 Header;
        u8  Len;
        u8  Type;
        u8  Cmd;
        u8  Num;
        u16 Data;
        u16 Check;
    }prot;
    }Open20MsData,OpenGoCharge;

    //下发轮子速度结构体
    union TXRobotData1
    {
    u8 data[16];
    struct
    {
        u16 Header;
        u8  Len;
        u8  Type;
        u8  Cmd;
        u8  Num; 
        s16 Mode;
        s16 Vx;
        float Vz;   
        u16 Check;
    }prot;
    }TXRobotData1;

public:
    ChassisSerialPort(const std::string& port_name, uint baud_rate = 115200);

    ~ChassisSerialPort();

    void InitSerialPort(const std::string& port_name, uint baud_rate);

    void StartRecvChassisData();

    // 设置底盘速度
    void SetSpeed(float Vx, float Vz);

    // 设置句柄
    void SetUDPServer(UDPServer* pUDPServer);

    void Run();

private:
    boost::asio::io_context mIoContext;

    boost::asio::serial_port mSerialPort;

    UDPServer* mpUDPServer;
};
}

#endif