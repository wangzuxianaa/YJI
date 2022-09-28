#include "System.h"
#include <thread>
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace YJI
{
    System::System(const string& strSettingsFile)
    {
        std::cout << "Succeed to open setting file at:" << strSettingsFile << std::endl;

        // 主线程可以用来接收盘货请求

        // 创建UDP接收线程，接收导航电脑的数据
        mpUDPServer = new UDPServer(9090);


        mptUDPServer = new thread(&YJI::UDPServer::Run,
                            mpUDPServer);

        // 创建底盘串口线程收发底盘数据
        mpChassisSerialPort = new ChassisSerialPort("/dev/USB0", 115200);


        mptChassisSerialPort = new thread(&YJI::ChassisSerialPort::Run,
                                            mpChassisSerialPort);

        mpSystemMonitor = new SystemMonitor("/dev", 9600);

        mptSystemMonitor = new thread(&YJI::SystemMonitor::Run,
                                        mpSystemMonitor);
    }

    void System::Shutdown()
    {

    }
} // namespace YJI
