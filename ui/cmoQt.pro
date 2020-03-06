#-------------------------------------------------
#
# Project created by QtCreator 2019-09-14T15:37:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cmoQt
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

CONFIG += c++17

SOURCES += \
        bestparametrs.cpp \
        buffer.cpp \
        cell.cpp \
        cmo_system.cpp \
        device.cpp \
        generator.cpp \
        main.cpp \
        mainwindow.cpp \
        request.cpp \
        resultstable.cpp \
        secdialog.cpp \
        steps.cpp

HEADERS += \
        bestparametrs.h \
        buffer.hpp \
        cell.hpp \
        cmo_system.hpp \
        device.hpp \
        generator.hpp \
        mainwindow.h \
        request.hpp \
        resultstable.h \
        secdialog.h \
        statictis.h

FORMS += \
        bestparametrs.ui \
        mainwindow.ui \
        resultstable.ui \
        secdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
