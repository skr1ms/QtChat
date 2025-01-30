#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clienthandler.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QSqlQueryModel(this))
    , serverRunning(false)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("chatdb");
    db.setUserName("root");
    db.setPassword("Got_milk3");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return;
    }

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }

    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed." << std::endl;
        WSACleanup();
        return;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed." << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed." << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return;
    }
    serverRunning = true;

    // Start accepting connections in a separate thread
    QThread *acceptThread = QThread::create([this]() {
        while (serverRunning) {
            SOCKET clientSocket = accept(listenSocket, NULL, NULL);
            if (clientSocket == INVALID_SOCKET) {
                std::cerr << "Accept failed." << std::endl;
                continue;
            }
            ClientHandler *handler = new ClientHandler(clientSocket, db);
            handler->start();
        }
    });
    acceptThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    closesocket(listenSocket);
    WSACleanup();
}
void MainWindow::on_stopButton_clicked()
{
    if (serverRunning) {
        closesocket(listenSocket);
        serverRunning = false;
        ui->stopButton->setEnabled(false);
        QMessageBox::information(this, "Server Stopped", "Server has been stopped");
    }
}

void MainWindow::on_showusersButton_clicked()
{
    model->setQuery("SELECT * FROM users_list");
    if (model->lastError().isValid()) {
        qDebug() << "Query error:" << model->lastError().text();
    } else {
        ui->userView->setModel(model);
    }
}
void MainWindow::on_publicButton_clicked()
{
    model->clear();
    model = new QSqlQueryModel(this);
    model->setQuery("select * from all_chat");
    if (model->lastError().isValid()) {
        qDebug() << "Query error:" << model->lastError().text();
    } else {
        ui->messagesView->setModel(model);
        ui->messagesView->resizeColumnsToContents();
    }
}
void MainWindow::on_privateButton_clicked()
{
    model->clear();
    model = new QSqlQueryModel(this);
    model->setQuery("select messages_storage.message, messages_storage.sent_date, u1.login AS from_login, u2.login AS to_login from messages_storage join users_list u1 ON messages_storage.from_id=u1.id JOIN users_list u2 ON messages_storage.to_id=u2.id");
    if (model->lastError().isValid()) {
        qDebug() << "Query error:" << model->lastError().text();
    } else {
        ui->messagesView->setModel(model);
        ui->messagesView->resizeColumnsToContents();
    }
}
void MainWindow::on_offButton_clicked()
{
    std::string tmp_login=ui->userEdit->text().toStdString();
    auto it = std::find(ClientHandler::connectedUsers.begin(), ClientHandler::connectedUsers.end(), tmp_login);
    if (it != ClientHandler::connectedUsers.end()) {
        ClientHandler::connectedUsers.erase(it);
        QMessageBox::information(this, "User Disconnected", "User has been disconnected");
    } else {
        QMessageBox::warning(this, "User Not Found", "User not found in the connected users list");
    }

}
void MainWindow::on_banUserButton_clicked()
{
    int qm_flag=0;
    std::string log=ui->userEdit->text().toStdString();
    QSqlQuery query(db);
    query.prepare("SELECT login, password FROM users_list");
    if (query.exec()) {
        while (query.next()) {
            std::string dbLogin = query.value(0).toString().toStdString();
            if (dbLogin == log) {
                query.prepare("UPDATE users_list SET ban_status = true WHERE login=:login");
                query.bindValue(":login",ui->userEdit->text());
                if(query.exec())
                {
                    QMessageBox::information(this, tr("Info"), ui->userEdit->text()+" has been banned");
                    qm_flag++;
                }
                else
                {
                    QMessageBox::critical(this,tr("Error"), "Unexpected error");
                }
            }
        }
        if(qm_flag==0)
        {
            QMessageBox::critical(this,tr("Error"), "wrong username!");
        }
        else
        {
             qm_flag--;
        }
    } else {
        QMessageBox::critical(this,tr("Error"), "wrong username!");
        qDebug() << "Query error:" << query.lastError().text();
    }
}


void MainWindow::on_onButton_clicked()
{
    int qm_flag=0;
    std::string log=ui->userEdit->text().toStdString();
    QSqlQuery query(db);
    query.prepare("SELECT login, password FROM users_list");
    if (query.exec()) {
        while (query.next()) {
            std::string dbLogin = query.value(0).toString().toStdString();
            if (dbLogin == log) {
                query.prepare("UPDATE users_list SET ban_status = false WHERE login=:login");
                query.bindValue(":login",ui->userEdit->text());
                if(query.exec())
                {
                    QMessageBox::information(this, tr("Info"), ui->userEdit->text()+" has been unbanned");
                    qm_flag++;
                }
                else
                {
                    QMessageBox::critical(this,tr("Error"), "Unexpected error");
                }
            }
        }
        if(qm_flag==0)
        {
            QMessageBox::critical(this,tr("Error"), "wrong username!");
        }
        else{
            qm_flag--;
        }
    } else {
        qDebug() << "Query error:" << query.lastError().text();
    }
}


void MainWindow::on_actionclose_triggered()
{
    this->close();
}

