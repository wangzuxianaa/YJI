#ifndef CHASSISSERIALPORT_H
#define CHASSISSERIALPORT_H

#include <boost/asio.hpp>

namespace YJI
{

class ChassisSerialPort
{
public:
    ChassisSerialPort(const std::string& port_name, uint baud_rate = 115200);

    void InitSerialPort(const std::string& port_name, uint baud_rate);

    void StartReceive();

    

private:
    boost::asio::io_context mIoContext;

    // 波特率
    uint mBaudRate;

    // 串口名
    std::string mPortName;

    std::shared_ptr<boost::asio::serial_port> mpSerialPort;
};
}

#endif