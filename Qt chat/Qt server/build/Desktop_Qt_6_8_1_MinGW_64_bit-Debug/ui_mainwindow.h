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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionclose;
    QAction *actionwork_in_progress;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLineEdit *userEdit;
    QLabel *label;
    QTableView *userView;
    QPushButton *showusersButton;
    QPushButton *offButton;
    QPushButton *onButton;
    QPushButton *banUserButton;
    QPushButton *stopButton;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QTableView *messagesView;
    QHBoxLayout *horizontalLayout;
    QPushButton *publicButton;
    QPushButton *privateButton;
    QMenuBar *menubar;
    QMenu *menuclose;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(940, 597);
        actionclose = new QAction(MainWindow);
        actionclose->setObjectName("actionclose");
        actionwork_in_progress = new QAction(MainWindow);
        actionwork_in_progress->setObjectName("actionwork_in_progress");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        userEdit = new QLineEdit(tab);
        userEdit->setObjectName("userEdit");

        verticalLayout_2->addWidget(userEdit);

        label = new QLabel(tab);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        userView = new QTableView(tab);
        userView->setObjectName("userView");

        verticalLayout_2->addWidget(userView);

        showusersButton = new QPushButton(tab);
        showusersButton->setObjectName("showusersButton");

        verticalLayout_2->addWidget(showusersButton);

        offButton = new QPushButton(tab);
        offButton->setObjectName("offButton");

        verticalLayout_2->addWidget(offButton);

        onButton = new QPushButton(tab);
        onButton->setObjectName("onButton");

        verticalLayout_2->addWidget(onButton);

        banUserButton = new QPushButton(tab);
        banUserButton->setObjectName("banUserButton");

        verticalLayout_2->addWidget(banUserButton);

        stopButton = new QPushButton(tab);
        stopButton->setObjectName("stopButton");
        stopButton->setStyleSheet(QString::fromUtf8("QPushButton{background-color:#ff0509;}"));

        verticalLayout_2->addWidget(stopButton);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(tab_2);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        messagesView = new QTableView(tab_2);
        messagesView->setObjectName("messagesView");

        verticalLayout_3->addWidget(messagesView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        publicButton = new QPushButton(tab_2);
        publicButton->setObjectName("publicButton");

        horizontalLayout->addWidget(publicButton);

        privateButton = new QPushButton(tab_2);
        privateButton->setObjectName("privateButton");

        horizontalLayout->addWidget(privateButton);


        verticalLayout_3->addLayout(horizontalLayout);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 940, 22));
        menuclose = new QMenu(menubar);
        menuclose->setObjectName("menuclose");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuclose->menuAction());
        menuclose->addSeparator();
        menuclose->addAction(actionclose);
        menuclose->addAction(actionwork_in_progress);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionclose->setText(QCoreApplication::translate("MainWindow", "close", nullptr));
        actionwork_in_progress->setText(QCoreApplication::translate("MainWindow", "work in progress....", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Input user login to turn off him or ban.", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "On this page u can ban users and show users list.", nullptr));
        showusersButton->setText(QCoreApplication::translate("MainWindow", "show all users", nullptr));
        offButton->setText(QCoreApplication::translate("MainWindow", "Turn off user", nullptr));
        onButton->setText(QCoreApplication::translate("MainWindow", "Unban user", nullptr));
        banUserButton->setText(QCoreApplication::translate("MainWindow", "Ban user", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop server", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "On this page u can check all messages.", nullptr));
        publicButton->setText(QCoreApplication::translate("MainWindow", "Show all chat", nullptr));
        privateButton->setText(QCoreApplication::translate("MainWindow", "Show private messages", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        menuclose->setTitle(QCoreApplication::translate("MainWindow", "menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
