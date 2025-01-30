#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

class NetworkManager
{
public:
    explicit NetworkManager();
    ~NetworkManager();
    bool connectToServer();
    void disconnect();
    void sendData(const std::string &data);
    std::string receiveData();
    bool checkConnection();
    int close_con_counter=0;

private:
    SOCKET clientSocket;
    char buffer[BUFFER_SIZE];
    bool conFlag=false;
};

#endif // NETWORKMANAGER_H
