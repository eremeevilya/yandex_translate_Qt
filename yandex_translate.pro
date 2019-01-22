#-------------------------------------------------
#
# Project created by QtCreator 2018-08-19T20:45:58
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Добавляем компанию, версию, права
VERSION = 1.2.1
QMAKE_TARGET_COMPANY = Eremeew Ilya
QMAKE_TARGET_PRODUCT = Yandex Translate
QMAKE_TARGET_COPYRIGHT = eremeew

TARGET = yandex_translate
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
        translate_widget.cpp \
    network_translate.cpp

HEADERS += \
        translate_widget.h \
    network_translate.h

FORMS += \
        translate_widget.ui

RC_ICONS = images/icon.ico

RESOURCES += \
    res.qrc
