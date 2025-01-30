#ifndef LOGINFORM_H
#define LOGINFORM_H
#include <QWidget>
#include <QMessageBox>
#include "mainwindow.h"
#include "networkmanager.h"

namespace Ui {
class LoginForm;
}
class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    void setCon(std::shared_ptr <NetworkManager> con);
    ~LoginForm();
signals:
    void onRegF();
    void accepted(std::string userlogin);
    void rejected();

private slots:
    void on_actionButtons_accepted();
    void on_actionButtons_rejected();

    void on_registrationButton_clicked();

private:
    Ui::LoginForm *ui;
    std::shared_ptr <NetworkManager> netw;
    bool con_flag;
};

#endif // LOGINFORM_H
