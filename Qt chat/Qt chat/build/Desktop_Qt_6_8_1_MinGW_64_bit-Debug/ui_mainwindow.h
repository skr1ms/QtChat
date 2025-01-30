/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionclose_client;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *chatLineEdit;
    QPushButton *sendToAllButton;
    QPushButton *sendPrivateButton;
    QPushButton *logoutButton;
    QSplitter *splitter;
    QTextBrowser *publicBrowser;
    QTextBrowser *privateBrowser;
    QMenuBar *menubar;
    QMenu *menuType_here;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(667, 329);
        actionclose_client = new QAction(MainWindow);
        actionclose_client->setObjectName("actionclose_client");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        chatLineEdit = new QLineEdit(centralwidget);
        chatLineEdit->setObjectName("chatLineEdit");

        horizontalLayout->addWidget(chatLineEdit);

        sendToAllButton = new QPushButton(centralwidget);
        sendToAllButton->setObjectName("sendToAllButton");

        horizontalLayout->addWidget(sendToAllButton);

        sendPrivateButton = new QPushButton(centralwidget);
        sendPrivateButton->setObjectName("sendPrivateButton");

        horizontalLayout->addWidget(sendPrivateButton);

        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");
        QFont font;
        font.setPointSize(13);
        logoutButton->setFont(font);
        logoutButton->setCursor(QCursor(Qt::CursorShape::CrossCursor));
        logoutButton->setStyleSheet(QString::fromUtf8("QPushButton {background-color:#e80000;}"));

        horizontalLayout->addWidget(logoutButton);


        verticalLayout->addLayout(horizontalLayout);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        publicBrowser = new QTextBrowser(splitter);
        publicBrowser->setObjectName("publicBrowser");
        splitter->addWidget(publicBrowser);
        privateBrowser = new QTextBrowser(splitter);
        privateBrowser->setObjectName("privateBrowser");
        splitter->addWidget(privateBrowser);

        verticalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 667, 22));
        menuType_here = new QMenu(menubar);
        menuType_here->setObjectName("menuType_here");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuType_here->menuAction());
        menuType_here->addAction(actionclose_client);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionclose_client->setText(QCoreApplication::translate("MainWindow", "close client", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Your message:", nullptr));
        sendToAllButton->setText(QCoreApplication::translate("MainWindow", "send to all", nullptr));
        sendPrivateButton->setText(QCoreApplication::translate("MainWindow", "send private", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "logout", nullptr));
        menuType_here->setTitle(QCoreApplication::translate("MainWindow", "menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
