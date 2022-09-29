#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <mutex>
#include "Common.h"

using boost::asio::ip::udp;
using boost::asio::serial_port;

namespace YJI
{
class Common;
class System;
class ChassisSerialPort;
 
class UDPServer 
{
public:
    UDPServer(const int port);

    ~UDPServer();

    void StartRecvUDPData();

    void StartSendUDPData(const std::string& message, boost::property_tree::ptree& SendTree, 
                            boost::property_tree::ptree& RecvTree);

    void SetChassisSerialPort(ChassisSerialPort* pChassisSerialPort);

    // 请求中止线程
    void RequestFinish();

    void Run();

protected:
    UDPMessage ResolveMessage(std::string str);

    inline std::string PtreeToJsonString(const boost::property_tree::ptree& tree) {
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        return ss.str();
    }

private:
    // UDP套接字
    udp::socket mSocket;

    // 客户端信息
    udp::endpoint mRemoteEndPoint;

    std::mutex mMutexAGVInfo;

    UDPMessage meMessage;

    boost::asio::io_context mIoContext;

    ChassisSerialPort* mpChassisSerialPort;

    char mRecvBuff[1024];
};
}

#endif
