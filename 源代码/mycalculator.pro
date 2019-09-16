#-------------------------------------------------
#
# Project created by QtCreator 2019-07-04T10:36:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mycalculator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    element.cpp \
    calculator.cpp

HEADERS += \
        mainwindow.h \
    calculator.h \
    element.h \
    ../build-mycalculator-Desktop_Qt_5_11_1_MSVC2017_64bit-Release/ui_mainwindow.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    icons.qrc

DISTFILES += \
    logo.rc

RC_ICONS = logo.ico


