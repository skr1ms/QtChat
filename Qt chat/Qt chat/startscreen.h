#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include <networkmanager.h>
#include <QDebug>
#include <QDialog>
#include <memory>
namespace Ui {
class StartScreen;
}

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);
    bool getConStatus();
    void setConStatus(bool flag);
    void loggedIn(std::string login);
    void toRegForm();
    void toLogForm();
    void logoutCon(std::shared_ptr<NetworkManager> networkManager);
    void setNetworkManager(std::shared_ptr<NetworkManager> networkManager);
    void resetNetworkManager(std::shared_ptr<NetworkManager> networkManager);
    void onReject();
    ~StartScreen();
private:
    Ui::StartScreen *ui;
    std::shared_ptr<NetworkManager> netw;
    bool con_status=true;
    std::string m_login="";
};

#endif // STARTSCREEN_H
