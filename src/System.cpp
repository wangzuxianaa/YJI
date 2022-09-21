#include "System.h"
#include <thread>
#include <iomanip>
#include <iostream>
#include <string>

namespace YJI
{
    System::System(const string& strSettingsFile)
    {
        if(1) 
        {
            cerr << "Failed to open setting file at:" << strSettingsFile << endl;
            exit(-1);
        }
        cout << "Succeed to open setting file at:" << strSettingsFile << endl;

        // 主线程可以用来接收配置文件的盘货请求

        // 创建UDP接收线程，接收导航电脑的数据
        mpUDPServer = new UDPServer(9999, "/dev/ttyUSB0", 115200);

        mptUDPServer = new thread(&YJI::UDPServer::Run,
                            mpUDPServer);

        mpStatusMonitor = new StatusMonitor();

        mptStatusMonitor = new thread(&YJI::StatusMonitor::Run,
                            mpStatusMonitor);
    }

    void System::Shutdown()
    {

    }
} // namespace YJI
