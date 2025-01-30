QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    loginform.cpp \
    main.cpp \
    mainwindow.cpp \
    networkmanager.cpp \
    registerform.cpp \
    startscreen.cpp

HEADERS += \
    loginform.h \
    mainwindow.h \
    networkmanager.h \
    registerform.h \
    startscreen.h

FORMS += \
    loginform.ui \
    mainwindow.ui \
    registerform.ui \
    startscreen.ui
LIBS += -lws2_32
TRANSLATIONS += \
    QT_version_of_chat_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
