#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::string userlogin, std::shared_ptr<NetworkManager> nw, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , netw(nw)
    , m_login(userlogin)
{
    ui->setupUi(this);
    auto timer= new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::chatUpdate);
    timer->start(5000);
}

MainWindow::~MainWindow()
{
    if(netw!=nullptr && netw->checkConnection() && netw->close_con_counter<0)
    {
        netw->disconnect();
        delete ui;
        qApp->exit(0);
    }
    else{
        delete ui;

    }

}

void MainWindow::on_actionclose_client_triggered()
{
    netw->disconnect();
    this->close();
}


void MainWindow::on_sendToAllButton_clicked()
{
    std::string server_str = "**" +getUserLogin()+ "*L" + ui->chatLineEdit->text().toStdString();
    netw->sendData(server_str);
    std::string response=netw->receiveData();
}
void MainWindow::on_sendPrivateButton_clicked()
{
    QDialog dial(this);
    dial.setModal(true);
    auto l=new QVBoxLayout();
    dial.setLayout(l);
    auto userListWgt = new QListWidget(&dial);
    l->addWidget(userListWgt);
    auto buttonBox = new QDialogButtonBox (QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dial);
    l->addWidget(buttonBox);
    connect (buttonBox, &QDialogButtonBox::accepted, &dial, &QDialog::accept);
    connect (buttonBox, &QDialogButtonBox::rejected, &dial, &QDialog::reject);
    l->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, &dial, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dial, &QDialog::reject);
    std::string server_str = "*U";
    netw->sendData(server_str);
    std::string response = netw->receiveData();
    std::vector<std::string> elements;
    std::istringstream stream(response);
    std::string line;
    while (std::getline(stream, line)) {
        elements.push_back(line);
    }
    for(auto user : elements)
    {
        userListWgt->addItem(QString::fromStdString(user));
    }
    userListWgt->setCurrentRow(0);
    auto result=dial.exec();
    if(result=QDialog::Accepted && userListWgt->currentItem())
    {
        std::string recipient_login=userListWgt->currentItem()->text().toStdString();
        std::string message=ui->chatLineEdit->text().toStdString();
        int check = message.find("*");
        if (check != -1)
        {
           QMessageBox::information(this,"Info","your message has * symbol, please change message and try again");
        }
        server_str="";
        server_str = "*P" + recipient_login + "*M" + message + "*S" + getUserLogin();
        netw->sendData(server_str);
        auto response = netw->receiveData();
    }
}


void MainWindow::on_logoutButton_clicked()
{
    auto startScreen1=StartScreen();
    startScreen1.resetNetworkManager(netw);
    //startScreen1->show();
    auto result = startScreen1.exec();
    netw->close_con_counter--;
    this->close();
}

std::string MainWindow::getUserLogin()
{
    return m_login;
}

void MainWindow::chatUpdate()
{
    std::string server_str = "!*";
    netw->sendData(server_str);
    std::string response=netw->receiveData();
    std::vector<std::string> elements;
    std::istringstream stream(response);
    std::string line;
    while (std::getline(stream, line)) {
        elements.push_back(line);
    }
    QString chat;
    for(const auto &msg : elements)
    {
        chat.append(QString::fromStdString(msg) + "\n");
    }
    ui->publicBrowser->setText(chat);
    chat.clear();
    elements.clear();
    server_str="";
    response = "";
    server_str = "*8"+getUserLogin();
    netw->sendData(server_str);
    if(response=="You don't have messages")
    {
        QMessageBox::critical(this, tr("Info"), tr("you do not have personal messages"));
        return;
    }
    response=netw->receiveData();
    if(response=="you has been kicked by admin"){
        QMessageBox::critical(this, tr("Error"), tr("you has been kicked by admin"));
        qApp->exit(0);
    }
    if(response == "You has been banned by administrator")
    {
        QMessageBox::critical(this, tr("Error"), tr("You has been banned by administrator"));
        qApp->exit(0);
    }
    std::istringstream stream1 (response);
    std::string line1;
    while (std::getline(stream1, line1)) {
        elements.push_back(line1);
    }
    for(const auto &msg : elements)
    {
        chat.append(QString::fromStdString(msg) + "\n");
    }
    ui->privateBrowser->setText(chat);
    chat.clear();
    elements.clear();
}

