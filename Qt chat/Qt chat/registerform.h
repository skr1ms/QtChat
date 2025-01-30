#ifndef REGISTERFORM_H
#define REGISTERFORM_H
#include <memory>
#include "networkmanager.h"
#include <QWidget>

namespace Ui {
class RegisterForm;
}

class RegisterForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterForm(QWidget *parent = nullptr);
    ~RegisterForm();
    void setCon(std::shared_ptr<NetworkManager> con);
private slots:
    void on_loginButton_clicked();

    void on_actionButtons_accepted();

    void on_actionButtons_rejected();

signals:
    void onLogF();
    void rejected();
private:
    Ui::RegisterForm *ui;
    std::shared_ptr<NetworkManager> netw;
};

#endif // REGISTERFORM_H
