#ifndef SERIAL_MONITOR_HPP
#define SERIAL_MONITOR_HPP

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <signal.h>

class SerialMonitor {
public:
    SerialMonitor() = default;
    ~SerialMonitor() = default;
    void configure();
    void start();
    void close();
private:
    HANDLE h_serial;
    DWORD dwRead;
    OVERLAPPED osReader = {0};
    char buffer[100] = {0};
};

#endif