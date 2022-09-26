#include "ChassisSerialPort.h"
#include <iostream>

namespace YJI
{
ChassisSerialPort::ChassisSerialPort(const std::string& port_name, uint baud_rate):mPortName(port_name), 
                                                                                mBaudRate(baud_rate)
{
    InitSerialPort(port_name, baud_rate);
}

void ChassisSerialPort::InitSerialPort(const std::string& port_name, uint baud_rate)
{
    try
    {
        mpSerialPort = std::make_shared<boost::asio::serial_port>(new boost::asio::serial_port(mIoContext, port_name));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
    // 设置波特率
    mpSerialPort->set_option(boost::asio::serial_port::baud_rate(baud_rate));
}

}