#include "registerform.h"
#include "ui_registerform.h"
#include <QMessageBox>
RegisterForm::RegisterForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterForm)
{
    ui->setupUi(this);
}
RegisterForm::~RegisterForm()
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
void RegisterForm::setCon(std::shared_ptr<NetworkManager> con)
{
    netw=con;
}
void RegisterForm::on_loginButton_clicked()
{
     onLogF();
}
void RegisterForm::on_actionButtons_accepted()
{
    if(ui->passwordEdit->text() != ui->confirmPasswordEdit->text())
    {
        QMessageBox::critical(this, tr("Error"), tr("Passwords not match"));
        return;
    }
    std::string login = ui->loginEdit->text().toStdString();
    std::string password = ui->passwordEdit->text().toStdString();
    std::string server_str = "*L" + login + "*P" + password;
    netw->sendData(server_str);
    std::string response = netw->receiveData();
    if(response!="")
    {
        QMessageBox::information(this,"Info",QString::fromStdString(response));
    }
    else{
        QMessageBox::critical(this, tr("Error"), tr("Something went wrong...."));
        qApp->exit(0);
    }
}
void RegisterForm::on_actionButtons_rejected()
{
    rejected();
}

