/********************************************************************************
** Form generated from reading UI file 'startscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTSCREEN_H
#define UI_STARTSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "loginform.h"
#include "registerform.h"

QT_BEGIN_NAMESPACE

class Ui_StartScreen
{
public:
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    LoginForm *LoginPage;
    RegisterForm *RegisterPage;

    void setupUi(QWidget *StartScreen)
    {
        if (StartScreen->objectName().isEmpty())
            StartScreen->setObjectName("StartScreen");
        StartScreen->resize(488, 351);
        horizontalLayout = new QHBoxLayout(StartScreen);
        horizontalLayout->setObjectName("horizontalLayout");
        stackedWidget = new QStackedWidget(StartScreen);
        stackedWidget->setObjectName("stackedWidget");
        LoginPage = new LoginForm();
        LoginPage->setObjectName("LoginPage");
        stackedWidget->addWidget(LoginPage);
        RegisterPage = new RegisterForm();
        RegisterPage->setObjectName("RegisterPage");
        stackedWidget->addWidget(RegisterPage);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(StartScreen);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(StartScreen);
    } // setupUi

    void retranslateUi(QWidget *StartScreen)
    {
        StartScreen->setWindowTitle(QCoreApplication::translate("StartScreen", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartScreen: public Ui_StartScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTSCREEN_H
