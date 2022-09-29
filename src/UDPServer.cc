#include "UDPServer.h"
#include "System.h"
#include <iostream>
#include <string>


namespace YJI
{
UDPServer::UDPServer(const int port) : mSocket(mIoContext, udp::endpoint(udp::v4(), port))
{
    if(mSocket.is_open())
    {
        std::cout << "Init Socket Successfully" << std::endl;
    }
    else 
    {
        std::cerr << "Fail to Init Socket" << std::endl;
    }
}

UDPServer::~UDPServer()
{
    if(mSocket.is_open())
    {
        mSocket.cancel();
        mSocket.close();
        std::cout << "Socket is closed" << std::endl;
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
                    // if(it->first == "Final_Pose")
                    // {
                    //     auto pt = RecvPtree.get_child("Final_Pose");
                    //     for(auto it2 = pt.begin(); it2 != pt.end(); it2++)
                    //     {
                    //     }
                    // }
                    // else if(it->first == "Linear")
                    // {
                        
                    // }
                    // else if(it->first == "Angular")
                    // {
                        
                    // }
                    StartSendUDPData(it->first, SendPtree, RecvPtree);
                }
            } 
        });
}

void UDPServer::StartSendUDPData(const std::string& message, boost::property_tree::ptree& SendTree, boost::property_tree::ptree& RecvTree)
{
    // 根据接收类型发数据
    switch (ResolveMessage(message))
    {
    case UDPMessage::Linear:
        // 线速度
        AGV_Vel.Linear = RecvTree.get<float>(message);
        break;
    case UDPMessage::Angular:
        // 角速度
        AGV_Vel.Angular = RecvTree.get<float>(message);
        break;
    case UDPMessage::Charger_Switch:
        // 充电开关
        ChargerSwitch = RecvTree.get<bool>(message);
        break;
    case UDPMessage::Final_Pose:
        // 小车定位位置 
        {
            auto pt = RecvTree.get_child("Final_Pose");
            int index = 0;
            for(auto it = pt.begin(); it != pt.end(); it++, index++)
            {
                if(index == 0) {
                    AGV_Pos.AGVX = it->second.get_value<float>();
                } else if(index == 1) {
                    AGV_Pos.AGVY = it->second.get_value<float>();
                } else if(index == 2) {
                    AGV_Pos.AGVYaw = it->second.get_value<float>();
                }
            }      
            break;
        }
    case UDPMessage::Power_State:
        // 电源开关
        SendTree.put("Power_State", true);
        break;
    case UDPMessage::Button_Stop:
        // 急停按钮
        SendTree.put("Button_Stop", false);
        break;
    case UDPMessage::Charge_State:
        // 充电状态
        SendTree.put("Charge_State", false);
        break;
    case UDPMessage::Motor_Lock_State:
        // 电机
        SendTree.put("Motor_Lock_State", false);
        break;
    case UDPMessage::Position:
        // 小车位置
        SendTree.put("Position", AGV_Pos.AGVX);
        SendTree.put("Position", AGV_Pos.AGVY);
        break;
    case UDPMessage::Rotation:
        // 小车偏航角
        SendTree.put("Rotation", AGV_Pos.AGVYaw);
        break;
    case UDPMessage::Twist:
        // 小车线速度和角速度
        {
            unique_lock<std::mutex> lock(mMutexAGVInfo);
            SendTree.put("Twist", (float) AGV_Info.Vx / 1000.0);
            SendTree.put("Twist", (float) AGV_Info.Vz);
            break;
        }
    case UDPMessage::Percent:
        // 小车电量
        SendTree.put("Percent", 50.0f);
        break;
    case UDPMessage::Voltage:
        //  小车电压
        {
            unique_lock<std::mutex> lock(mMutexAGVInfo);
            SendTree.put("Voltage", (float)AGV_Info.Voltage / 10.0);
            break;
        }
    case UDPMessage::Current:
        // 小车电流
        SendTree.put("Current", 20.0f);
        break;
    default:
        break;
    }
    mSocket.send_to(boost::asio::buffer(PtreeToJsonString(SendTree)), mRemoteEndPoint);
}

void UDPServer::SetChassisSerialPort(ChassisSerialPort* pChassisSerialPort)
{
    mpChassisSerialPort = pChassisSerialPort;
}

UDPMessage UDPServer::ResolveMessage(std::string str)
{

    if(str == "Linear")           return UDPMessage::Linear;
    if(str == "Angular")          return UDPMessage::Angular;
    if(str == "Charger_Switch")   return UDPMessage::Charger_Switch;
    if(str == "Final_Pose")       return UDPMessage::Final_Pose;
    if(str == "Power_State")      return UDPMessage::Power_State;
    if(str == "Button_Stop")      return UDPMessage::Button_Stop;
    if(str == "Charge_State")     return UDPMessage::Charge_State;
    if(str == "Motor_Lock_State") return UDPMessage::Motor_Lock_State;
    if(str == "Position")         return UDPMessage::Position;
    if(str == "Rotation")         return UDPMessage::Rotation;
    if(str == "Twist")            return UDPMessage::Twist;
    if(str == "Percent")          return UDPMessage::Percent;
    if(str == "Voltage")          return UDPMessage::Voltage;
    if(str == "Current")          return UDPMessage::Current;
    return UDPMessage::Invalid;
}

void UDPServer::Run()
{
    try {
        StartRecvUDPData();
        mIoContext.run();
    } catch (const std::exception& ex){
        std::cerr << ex.what() << std::endl;
    }
}
}