#ifndef SYSTEM_H
#define SYSTEM_H

#include<string>
#include<thread>

#include "SystemMonitor.h"
#include "UDPServer.h"
#include "ChassisSerialPort.h"

using namespace std;

namespace YJI
{

class UDPServer;
class SystemMonitor;
class ChassisSerialPort;
class Common;

class System
{
public:
    System(const string& strSettingsFile);

    void Shutdown();

private:

    UDPServer* mpUDPServer;

    SystemMonitor* mpSystemMonitor;

    ChassisSerialPort* mpChassisSerialPort;

    std::thread* mptUDPServer;

    std::thread* mptSystemMonitor;

    std::thread* mptChassisSerialPort;

};

}

#endif