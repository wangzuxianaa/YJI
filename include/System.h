#ifndef SYSTEM_H
#define SYSTEM_H

#include<string>
#include<thread>

#include "StatusMonitor.h"
#include "UDPServer.h"

using namespace std;

namespace YJI
{

class UDPServer;

class System
{
public:
    System(const string& strSettingsFile);

    void Shutdown();

private:

    UDPServer* mpUDPServer;

    StatusMonitor* mpStatusMonitor;

    std::thread* mptUDPServer;

    std::thread* mptStatusMonitor;
};

}

#endif