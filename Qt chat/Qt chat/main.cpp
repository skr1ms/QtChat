#include "mainwindow.h"
#include "startscreen.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QT_version_of_chat_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    auto networkManager = std::make_shared<NetworkManager>();
    StartScreen startScreen;
    startScreen.setNetworkManager(networkManager);
    if(startScreen.getConStatus()==false)
    {
        QMessageBox::critical(&startScreen, ("Error"), ("Connection failed"));
        qApp->exit(0);
        //startScreen.show();
        return 0;
    }
    startScreen.show();
    return a.exec();

}
