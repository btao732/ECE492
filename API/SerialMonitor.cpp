#include "SerialMonitor.hpp"

bool running = true;

void signal_callback_handler(int signum) {
    std::cout << "Terminating" << std::endl;
    running = false;
}

SerialMonitor::SerialMonitor() {
    signal(SIGINT, signal_callback_handler);

    h_serial = CreateFile(_T("COM6"), GENERIC_READ | GENERIC_WRITE,
                            0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (h_serial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            std::cout << "COM6 Port Not Found" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    std::cout << "Connected on COM6" << std::endl;
    DCB dcbSerialParam = {0};
    dcbSerialParam.DCBlength = sizeof(dcbSerialParam);

    if (!GetCommState(h_serial, &dcbSerialParam)) {
        std::cout << "GetCommState error" << std::endl;
        CloseHandle(h_serial);  
        exit(EXIT_FAILURE);
    }

    dcbSerialParam.BaudRate = CBR_115200;
    dcbSerialParam.ByteSize = 8;
    dcbSerialParam.StopBits = ONESTOPBIT;
    dcbSerialParam.Parity = NOPARITY;

    if (!SetCommState(h_serial, &dcbSerialParam)) {
        std::cout << "SetCommState error" << std::endl;
        CloseHandle(h_serial);
        exit(EXIT_FAILURE);
    }

    COMMTIMEOUTS timeout = {0};
    timeout.ReadIntervalTimeout = 60;
    timeout.ReadTotalTimeoutConstant = 60;
    timeout.ReadTotalTimeoutMultiplier = 15;
    timeout.WriteTotalTimeoutConstant = 60;
    timeout.WriteTotalTimeoutMultiplier = 8;

    if (!SetCommTimeouts(h_serial, &timeout)) {
        std::cout << "SetCommTimeouts error" << std::endl;
        CloseHandle(h_serial);
        exit(EXIT_FAILURE);
    }

    osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (!osReader.hEvent) {
        std::cout << "CreateEvent error" << std::endl;
        CloseHandle(h_serial);
        exit(EXIT_FAILURE);
    }
}

SerialMonitor::~SerialMonitor() {
    CloseHandle(h_serial);
}

void SerialMonitor::start() {
    while (running) {
        if (!ReadFile(h_serial, buffer, 100, &dwRead, &osReader)) {
            if (GetLastError() != ERROR_IO_PENDING) {
                std::cout << "Error in communications" << std::endl;
            } 
        } else  {
            std::cout << buffer;
        }
        memset(buffer, 0, sizeof(buffer));
    }
}