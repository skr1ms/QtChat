#include "clienthandler.h"
#pragma comment(lib, "ws2_32.lib")
std::vector<std::string> ClientHandler::connectedUsers;
ClientHandler::ClientHandler(SOCKET clientSocket, QSqlDatabase db, QObject *parent)
    : QThread(parent), clientSocket(clientSocket), db(db)
{
}

void ClientHandler::run()
{
    char buffer[1024];
    int bytesReceived;
    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        std::string message(buffer, bytesReceived);
        qDebug() << "Received:" << QString::fromStdString(message);

        if (message.substr(0, 2) == "*L") {
            regUser(message);
        } else if (message.substr(0, 2) == "L*") {
            loginUser(message);
        } else if (message.substr(0, 2) == "*P") {
            personalMess(message);
        } else if (message.substr(0, 2) == "**") {
            sendPublicMessage(message);
        } else if (message.substr(0, 2) == "!*") {
            printPublicChatMes();
        } else if (message.substr(0, 2) == "*U") {
            showListOfUsers();
        } else if (message.substr(0, 2) == "*8") {
            showPersonalMessages(message);
        } else if (message == "*!!!*") {
            closesocket(clientSocket);
            break;
        }
    }
    closesocket(clientSocket);
}

void ClientHandler::turnOff()
{

}
void ClientHandler::showPersonalMessages(const std::string &mes)
{
    int user_id = 0;
    std::string user_login = mes.substr(2);
    std::string temp;
    QSqlQuery query(db);
    auto it = std::find(ClientHandler::connectedUsers.begin(), ClientHandler::connectedUsers.end(), locallogin);
    if (it == ClientHandler::connectedUsers.end()) {
        std::string kick_resp="you has been kicked by admin";
        send(clientSocket, kick_resp.c_str(), kick_resp.size(), 0);
        exit(1);
    }
    query.prepare("SELECT ban_status FROM users_list WHERE login = :login");
    query.bindValue(":login", QString::fromStdString(locallogin));
    if (query.exec()) {
        if(query.next()){
        std::string dbBan_status=query.value(0).toString().toStdString();
        //qDebug() <<dbBan_status;
        if(dbBan_status=="1"){
            std::string ban_resp="You has been banned by administrator";
            send(clientSocket, ban_resp.c_str(), ban_resp.size(), 0);
            exit(1);
        }
        }
    }
    query.prepare("SELECT id FROM users_list WHERE login = :login");
    query.bindValue(":login", QString::fromStdString(user_login));
    if (query.exec()) {
        if (query.next()) {
            user_id = query.value(0).toInt();
        } else {
            std::string response_to_client = "unknown error";
            send(clientSocket, response_to_client.c_str(), response_to_client.size(), 0);
            return;
        }
    } else {
        qDebug() << "Query error:" << query.lastError().text();
        return;
    }

    query.prepare("SELECT tb1.login, tb2.message, tb2.sent_date FROM users_list tb1 JOIN messages_storage tb2 ON tb1.id = tb2.from_id AND tb2.to_id = :user_id");
    query.bindValue(":user_id", user_id);
    if (query.exec()) {
        if (query.size() == 0) {
            std::string response_to_client = "You don't have messages";
            send(clientSocket, response_to_client.c_str(), response_to_client.size(), 0);
        } else {
            std::ostringstream oss;
            while (query.next()) {
                for (int i = 0; i < query.record().count(); ++i) {
                    oss << query.value(i).toString().toStdString() << "\t";
                }
                oss << "\n";
            }
            std::string response_to_client = oss.str();
            if(response_to_client=="")
                response_to_client="You don't have messages";
            send(clientSocket, response_to_client.c_str(), response_to_client.size(), 0);
        }
    } else {
        qDebug() << "Query error:" << query.lastError().text();
    }
}

void ClientHandler::showListOfUsers()
{
    std::string response_to_client;
    QSqlQuery query(db);
    query.prepare("SELECT login FROM users_list");
    if (query.exec()) {
        while (query.next()) {
            response_to_client += query.value(0).toString().toStdString() + "\n";
        }
        send(clientSocket, response_to_client.c_str(), response_to_client.size(), 0);
    } else {
        qDebug() << "Query error:" << query.lastError().text();
    }
}

void ClientHandler::printPublicChatMes()
{
    std::string response_to_client;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM all_chat");
    if (query.exec()) {
        if (query.size() == 0) {
            response_to_client = "There is no messages yet";
            send(clientSocket, response_to_client.c_str(), response_to_client.size(), 0);
            return;
        }
        while (query.next()) {
            response_to_client += query.value(0).toString().toStdString() + "\n";
        }
        send(clientSocket, response_to_client.c_str(), response_to_client.size(), 0);
    } else {
        qDebug() << "Query error:" << query.lastError().text();
    }
}

void ClientHandler::sendPublicMessage(const std::string &mes)
{
    int pos = mes.find("**");
    int end_pos = mes.find("*L");
    std::string input = "from: " + mes.substr(pos + 2, end_pos - 2) + ", message: " + mes.substr(end_pos + 2);
    QSqlQuery query(db);
    query.prepare("INSERT INTO all_chat(message) VALUES(:message)");
    query.bindValue(":message", QString::fromStdString(input));
    if (query.exec()) {
        std::string response_to_client = "message successfully delivered";
        send(clientSocket, response_to_client.c_str(), response_to_client.size(), 0);
    } else {
        qDebug() << "Query error:" << query.lastError().text();
    }
}

void ClientHandler::personalMess(const std::string &mes)
{
    std::time_t now = std::time(nullptr);
    std::tm *local_time = std::localtime(&now);
    char date_buffer[80];
    std::strftime(date_buffer, sizeof(date_buffer), "%Y-%m-%d %H:%M:%S", local_time);
    int pos = mes.find("*P");
    int mes_pos = mes.find("*S");
    int end_pos = mes.find("*M");
    std::string from_query = "SELECT id FROM users_list WHERE login = '" + mes.substr(mes_pos + 2) + "'";
    std::string to_query = "SELECT id FROM users_list WHERE login = '" + mes.substr(pos + 2, end_pos - 2) + "'";
    std::string temp;
    int from_id = 0;
    int to_id = 0;
    QSqlQuery query(db);
    query.prepare(from_query.c_str());
    if (query.exec()) {
        if (query.next()) {
            temp = query.value(0).toString().toStdString();
            from_id = std::stoi(temp);
        }
    } else {
        qDebug() << "Query error:" << query.lastError().text();
    }

    query.prepare(to_query.c_str());
    if (query.exec()) {
        if (query.next()) {
            temp = query.value(0).toString().toStdString();
            to_id = std::stoi(temp);
        } else {
            std::string response_to_client = "this user doesn't exist";
            send(clientSocket, response_to_client.c_str(), response_to_client.size(), 0);
            return;
        }
    } else {
        qDebug() << "Query error:" << query.lastError().text();
    }

    query.prepare("INSERT INTO messages_storage(id, from_id, to_id, message, sent_date) VALUES(default, :from_id, :to_id, :message, :sent_date)");
    query.bindValue(":from_id", from_id);
    query.bindValue(":to_id", to_id);
    query.bindValue(":message", QString::fromStdString(mes.substr(end_pos + 2, mes.length() - end_pos - mes.substr(mes_pos).length() - 2)));
    query.bindValue(":sent_date", QString::fromStdString(date_buffer));
    if (query.exec()) {
        std::string response_to_client = "message successfully delivered";
        send(clientSocket, response_to_client.c_str(), response_to_client.size(), 0);
    } else {
        qDebug() << "Query error:" << query.lastError().text();
    }
}

void ClientHandler::regUser(const std::string &mes)
{
    int pos = mes.find("*L");
    int end_pos = mes.find("*P");
    std::string input_str = "INSERT INTO users_list(id, login, password, ban_status) VALUES(default, :login, :password, :ban_status)";
    QSqlQuery query(db);
    query.prepare(input_str.c_str());
    query.bindValue(":login", QString::fromStdString(mes.substr(pos + 2, end_pos - 2)));
    query.bindValue(":password", QString::fromStdString(mes.substr(end_pos + 2)));
    query.bindValue(":ban_status",0);
    if (query.exec()) {
        std::string response_to_client = "Succsessfully registered";
        send(clientSocket, response_to_client.c_str(), response_to_client.size(), 0);
    } else {
        if (query.lastError().text().contains("Duplicate entry")) {
            std::string response_to_client = "this user already exist";
            send(clientSocket, response_to_client.c_str(), response_to_client.size(), 0);
        } else {
            qDebug() << "Query error:" << query.lastError().text();
        }
    }
}
void ClientHandler::loginUser(const std::string &mes)
{
    int pos = mes.find("L*");
    int end_pos = mes.find("P*");
    std::string login = mes.substr(pos + 2, end_pos - pos - 2);
    std::string password = mes.substr(end_pos + 2);

    QSqlQuery query(db);
    query.prepare("SELECT login, password, ban_status FROM users_list");
    if (query.exec()) {
        int flag = 0;
        while (query.next()) {
            std::string dbLogin = query.value(0).toString().toStdString();
            std::string dbPassword = query.value(1).toString().toStdString();
            std::string dbBan_status=query.value(2).toString().toStdString();
            //qDebug() << dbLogin << dbPassword <<dbBan_status;
            if (dbLogin == login) {
                flag++;
            }
            if (dbPassword == password) {
                flag++;
                if(dbBan_status == "1"){
                    std::string ban_resp="You has been banned by administrator";
                    send(clientSocket, ban_resp.c_str(), ban_resp.size(), 0);
                    exit(1);
                }
            }
        }
        std::string response = (flag == 2) ? "Succ" : "wrong login or password";
        if(flag==2) {
            connectedUsers.push_back(login);
            locallogin=login;
        };

        send(clientSocket, response.c_str(), response.size(), 0);
    } else {
        qDebug() << "Query error:" << query.lastError().text();
    }
}
