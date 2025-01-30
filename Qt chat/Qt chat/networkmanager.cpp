#include "networkmanager.h"

NetworkManager::NetworkManager() : clientSocket(INVALID_SOCKET) {}

NetworkManager::~NetworkManager()
{
    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
        WSACleanup();
    }
}

bool NetworkManager::connectToServer()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed with error: " << WSAGetLastError() << std::endl;
        return false;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    if (::connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed with error: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }
    conFlag=true;
    return true;
}

void NetworkManager::disconnect()
{
    std::string end = "*!!!*";
    send(clientSocket, end.c_str(), end.size(), 0);
    closesocket(clientSocket);
    WSACleanup();
}

void NetworkManager::sendData(const std::string &server_str)
{
    if (clientSocket != INVALID_SOCKET) {
        send(clientSocket, server_str.c_str(), server_str.size(), 0);
    }
}

std::string NetworkManager::receiveData()
{
    if (clientSocket != INVALID_SOCKET) {
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            return std::string(buffer);
        }
    }
    return "";
}

bool NetworkManager::checkConnection()
{
    if(conFlag)
        return true;
    return false;
}

