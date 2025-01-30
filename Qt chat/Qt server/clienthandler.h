#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>
#include <sstream>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ClientHandler : public QThread
{
    Q_OBJECT

public:
    explicit ClientHandler(SOCKET clientSocket, QSqlDatabase db, QObject *parent = nullptr);
    void run() override;
    static void turnOff();
    static std::vector<std::string> connectedUsers;
private:
    std::string locallogin;
    SOCKET clientSocket;
    QSqlDatabase db;
    void showPersonalMessages(const std::string &mes);
    void showListOfUsers();
    void printPublicChatMes();
    void sendPublicMessage(const std::string &mes);
    void personalMess(const std::string &mes);
    void regUser(const std::string &mes);
    void loginUser(const std::string &mes);
};

#endif // CLIENTHANDLER_H
