#ifndef STATUSMONITOR_H
#define STATUSMONITOR_H

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

namespace YJI
{

class System;

class SystemMonitor
{
public:
    struct RequestCmd
    {
        uint8_t SOI = 0x7E;
        uint8_t ADD = 0x10;
        uint8_t VER = 0x02;
        uint8_t LEN;
        uint8_t FUN;
    };
public:
    SystemMonitor(const std::string& port_name, const int baud_rate);

    ~SystemMonitor();

    void InitSerialPort(const std::string& port_name, const int baud_rate);

    void Run();

private:
    boost::asio::io_context mIoContext;
    boost::asio::serial_port mSerialPort;
}; 
}

#endif