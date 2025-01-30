#include "startscreen.h"
#include "ui_startscreen.h"
#include "loginform.h"
#include <QMessageBox>
StartScreen::StartScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartScreen)
{
    ui->setupUi(this);
    connect(ui->LoginPage, &LoginForm::accepted, this, &StartScreen::loggedIn);
    connect(ui->LoginPage, &LoginForm::onRegF, this, &StartScreen::toRegForm);
    connect(ui->RegisterPage, &RegisterForm::onLogF, this, &StartScreen::toLogForm);
    connect(ui->LoginPage, &LoginForm::rejected, this, &StartScreen::onReject);
    connect(ui->RegisterPage, &RegisterForm::rejected, this, &StartScreen::onReject);
}

bool StartScreen::getConStatus()
{
    return con_status;
}

void StartScreen::setConStatus(bool flag)
{
    con_status=flag;
}

void StartScreen::loggedIn(std::string login)
{
    m_login=login;
    auto mainWindow = new MainWindow(m_login, netw);
    //mainWindow->setNetworkManager(netw);
    mainWindow->setAttribute(Qt::WA_DeleteOnClose);
    mainWindow->show();
    this->close();
}

void StartScreen::toRegForm()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void StartScreen::toLogForm()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void StartScreen::logoutCon(std::shared_ptr<NetworkManager> networkManager)
{
    netw=networkManager;
}

void StartScreen::setNetworkManager(std::shared_ptr<NetworkManager> networkManager)
{
    netw = networkManager;
    bool flag = netw->connectToServer();
    if(flag==false)
    {
        setConStatus(flag);
        ui->LoginPage->setCon(netw);
        ui->RegisterPage->setCon(netw);
    }
    else
    {
        ui->LoginPage->setCon(netw);
        ui->RegisterPage->setCon(netw);
    }
}

void StartScreen::resetNetworkManager(std::shared_ptr<NetworkManager> networkManager)
{
    netw=networkManager;
    ui->LoginPage->setCon(netw);
    ui->RegisterPage->setCon(netw);
}

void StartScreen::onReject()
{
    netw->close_con_counter--;
    this->close();
}

StartScreen::~StartScreen()
{
    delete ui;
}
