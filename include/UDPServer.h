#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <nlohmann/json.hpp>

using boost::asio::ip::udp;
using boost::asio::serial_port;
using json = nlohmann::json;

namespace YJI
{
class System;

class UDPServer 
{
public:
    UDPServer(const int port, const std::string& port_name, const uint baud_rate);

    bool InitSerialPort(const std::string& port_name, const uint baud_rate);

    void StartRecvUDPData();

    void StartSendUDPData();

    void StartRecvSerialData();

    void StartSendSerialData();

    // 请求中止线程
    void RequestFinish();

    void Run();

private:
    // UDP套接字
    udp::socket mSocket;

    // 端口
    serial_port mSerialPort;

    std::string mPortName;

    uint mBaudRate;

    // 客户端信息
    udp::endpoint mRemoteEndPoint;

    boost::asio::io_context mIoContext;

    std::array<char, 1024> mRecvBuff;
};
}

#endif
