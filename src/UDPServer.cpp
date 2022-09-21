#include "UDPServer.h"
#include "System.h"
#include <iostream>
#include <string>

namespace YJI
{
UDPServer::UDPServer(const int port, const std::string& port_name, const uint baud_rate) : mSocket(mIoContext, udp::endpoint(udp::v4(), port)), 
                                                                                mSerialPort(mIoContext), mPortName(port_name), mBaudRate(baud_rate)

{
}

bool UDPServer::InitSerialPort(const string& port_name, const uint baud_rate)
{
    try
    {
        boost::system::error_code err;
        mSerialPort.open(port_name, err);
        
        mSerialPort.set_option(serial_port::baud_rate(baud_rate));
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return false;
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
                // auto j = json::parse(bytes_recvd);
                // for(auto item : j.items())
                // {
                
                // }
            } 
        });
}

void UDPServer::StartSendUDPData()
{
    
}

void UDPServer::StartRecvSerialData()
{

}

void UDPServer::StartSendSerialData()
{
    
}

void UDPServer::Run()
{
    try {
        if(InitSerialPort(mPortName, mBaudRate))
        {
            StartRecvUDPData();
            StartRecvSerialData();
            mIoContext.run();
        }
    } catch (const std::exception& ex){
        std::cerr << ex.what() << std::endl;
    }
}

}