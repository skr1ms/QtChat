#include "loginform.h"
#include "ui_loginform.h"
#include "networkmanager.h"
#include <QMessageBox>
LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

void LoginForm::setCon(std::shared_ptr<NetworkManager> con)
{
    netw=con;
}

LoginForm::~LoginForm()
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

void LoginForm::on_actionButtons_accepted()
{
    std::string login = ui->loginEdit->text().toStdString();
    std::string password = ui->passwordEdit->text().toStdString();
    std::string server_str = "L*" + login + "P*" + password;
    netw->sendData(server_str);
    std::string response = netw->receiveData();
    if(response=="You has been banned by administrator")
    {
        QMessageBox::critical(this, tr("Error"), tr("You has been banned by administrator"));
        qApp->exit(0);
    }
    if(response!="")
    {
        QMessageBox::information(this,"Info",QString::fromStdString(response));
        if(response=="Succ")
        {
            netw->close_con_counter++;
            accepted(login);
        }
    }
    else{
    QMessageBox::critical(this, tr("Error"), tr("Something went wrong...."));
        qApp->exit(0);
    }
}
void LoginForm::on_actionButtons_rejected()
{
    rejected();
}


void LoginForm::on_registrationButton_clicked()
{
    onRegF();
}

