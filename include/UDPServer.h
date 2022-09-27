#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Common.h"

using boost::asio::ip::udp;
using boost::asio::serial_port;

namespace YJI
{
class System;

class UDPServer 
{
public:
    UDPServer(const int port);

    ~UDPServer();

    void StartRecvUDPData();

    void StartSendUDPData(const Common::UDPMessage& message, boost::property_tree::ptree& tree);

    // 请求中止线程
    void RequestFinish();

    void Run();

protected:
    Common::UDPMessage ResolveMessage(std::string str);

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

    boost::asio::io_context mIoContext;

    // Common::UDPMessage meMessage;

    char mRecvBuff[1024];
};
}

#endif
