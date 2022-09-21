#ifndef STATUSMONITOR_H
#define STATUSMONITOR_H

namespace YJI
{

class System;

class StatusMonitor
{
public:
    enum eFollowStatus {
        Lost = 0,
        Tracking = 1,
    };

    enum eSystemStatus {
        Normal = 0,
        AGVError = 1,
        UAVError = 2,
    };
public:
    StatusMonitor();

    void Run();

private:

    eFollowStatus mFollowStatus;

    eSystemStatus mSystemStatus;
}; 
}

#endif