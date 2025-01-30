#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clienthandler.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_stopButton_clicked();
    void on_showusersButton_clicked();
    void on_publicButton_clicked();
    void on_privateButton_clicked();
    void on_offButton_clicked();
    void on_banUserButton_clicked();
    void on_onButton_clicked();
    void on_actionclose_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQueryModel *model;
    SOCKET listenSocket;
    bool serverRunning;
    void handleNewConnection();
};

#endif // MAINWINDOW_H
