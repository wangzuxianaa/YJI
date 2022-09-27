#include "SystemMonitor.h"
#include <iostream>

namespace YJI
{
StatusMonitor::StatusMonitor(const std::string& port_name, const int baud_rate) : mSerialPort(mIoContext)
{
    InitSerialPort(port_name, baud_rate);
}

StatusMonitor::~StatusMonitor()
{
    if(mSerialPort.is_open())
    {
        mSerialPort.cancel();
        mSerialPort.close();
    }
    mIoContext.stop();
    mIoContext.reset();
}

void StatusMonitor::InitSerialPort(const std::string& port_name, const int baud_rate)
{
    boost::system::error_code ec;

    if(mSerialPort.is_open()) {
        std::cout << "error : serial port is opened" << std::endl;
        return;
    }

    mSerialPort.open(port_name, ec);
    if(ec)
    {
        std::cout << "error : fail to open port_name = " << port_name 
                    << ", ec = " << ec.message().c_str() << std::endl;
        return;
    }

    mSerialPort.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
    mSerialPort.set_option(boost::asio::serial_port_base::character_size(8));
    mSerialPort.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
    mSerialPort.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
	mSerialPort.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
}

void StatusMonitor::Run()
{
    try {
        mIoContext.run();
    } catch (const std::exception& ex){
        std::cerr << ex.what() << std::endl;
    }
}
}