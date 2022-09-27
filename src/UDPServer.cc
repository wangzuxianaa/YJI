#include "UDPServer.h"
#include "System.h"
#include <iostream>
#include <string>

namespace YJI
{
UDPServer::UDPServer(const int port) : mSocket(mIoContext, udp::endpoint(udp::v4(), port))
{
    std::cout << "Init Socket Successfully" << std::endl;
    StartRecvUDPData();
}

UDPServer::~UDPServer()
{
    if(mSocket.is_open())
    {
        mSocket.cancel();
        mSocket.close();
    }
    mIoContext.stop();
    mIoContext.reset();
}

void UDPServer::StartRecvUDPData()
{
    // 套接字异步接收数据
    mSocket.async_receive_from(
        boost::asio::buffer(mRecvBuff), mRemoteEndPoint,
        [this](boost::system::error_code err, std::size_t bytes_recvd)
        {
            if(!err && bytes_recvd > 0) 
            {
                // 解析json数据
                boost::property_tree::ptree RecvPtree, SendPtree;
                std::string msg(mRecvBuff, bytes_recvd);
                std::stringstream ss(msg);
                boost::property_tree::read_json(ss, RecvPtree);
                for(auto it = RecvPtree.begin(); it != RecvPtree.end(); it++)
                {
                    std::cout << it->first << std::endl;
                    StartSendUDPData(ResolveMessage(msg), SendPtree);
                }
            } 
        });
}

void UDPServer::StartSendUDPData(const Common::UDPMessage& message, boost::property_tree::ptree& tree)
{
    switch (message)
    {
    case Common::UDPMessage::Linear:
        // 线速度
        break;
    case Common::UDPMessage::Angular:
        // 角速度
        break;
    case Common::UDPMessage::Charger_Switch:
        // 充电开关
        break;
    case Common::UDPMessage::Final_Pose:
        // 小车定位位置
        break;
    case Common::UDPMessage::Power_State:
        // 电源开关
        tree.put("Power_State", true);
        break;
    case Common::UDPMessage::Button_Stop:
        // 急停按钮
        tree.put("Button_Stop", false);
        break;
    case Common::UDPMessage::Charge_State:
        // 充电状态
        tree.put("Charge_State", false);
        break;
    case Common::UDPMessage::Motor_Lock_State:
        // 电机
        tree.put("Motor_Lock_State", false);
        break;
    case Common::UDPMessage::Position:
        // 小车位置
        break;
    case Common::UDPMessage::Rotation:
        // 小车偏航角
        break;
    case Common::UDPMessage::Twist:
        // 小车线速度和角速度
        break;
    case Common::UDPMessage::Percent:
        // 小车电量
        tree.put("Percent", 50.0f);
        break;
    case Common::UDPMessage::Voltage:
        //  小车电压
        break;
    case Common::UDPMessage::Current:
        // 小车电流
        tree.put("Current", 20.0f);
        break;
    default:
        break;
    }
    mSocket.send_to(boost::asio::buffer(PtreeToJsonString(tree)), mRemoteEndPoint);
}

Common::UDPMessage ResolveMessage(std::string str)
{
    if(str == "Linear")           return Common::UDPMessage::Linear;
    if(str == "Angular")          return Common::UDPMessage::Angular;
    if(str == "Charger_Switch")   return Common::UDPMessage::Charger_Switch;
    if(str == "Final_Pose")       return Common::UDPMessage::Final_Pose;
    if(str == "Power_State")      return Common::UDPMessage::Power_State;
    if(str == "Button_Stop")      return Common::UDPMessage::Button_Stop;
    if(str == "Charge_State")     return Common::UDPMessage::Charge_State;
    if(str == "Motor_Lock_State") return Common::UDPMessage::Motor_Lock_State;
    if(str == "Position")         return Common::UDPMessage::Position;
    if(str == "Rotation")         return Common::UDPMessage::Rotation;
    if(str == "Twist")            return Common::UDPMessage::Twist;
    if(str == "Percent")          return Common::UDPMessage::Percent;
    if(str == "Voltage")          return Common::UDPMessage::Voltage;
    if(str == "Current")          return Common::UDPMessage::Current;
    return Common::UDPMessage::Invalid;
}

void UDPServer::Run()
{
    try {
        mIoContext.run();
    } catch (const std::exception& ex){
        std::cerr << ex.what() << std::endl;
    }
}

}