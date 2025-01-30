#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDialog>
#include <QVBoxLayout>
#include <QListWidget>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QTimer>
#include <sstream>
#include "qdialogbuttonbox.h"
#include "networkmanager.h"
#include "startscreen.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::string userlogin, std::shared_ptr<NetworkManager> nw, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionclose_client_triggered();
    void on_sendToAllButton_clicked();
    void on_sendPrivateButton_clicked();
    void on_logoutButton_clicked();
    std::string getUserLogin();
    void chatUpdate();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<NetworkManager> netw;
    std::string m_login;
};
#endif // MAINWINDOW_H
