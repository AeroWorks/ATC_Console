#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T19:35:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ATCConsole
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    consolecommands.cpp \
    atcdialog.cpp \
    dialogmainmenu.cpp \
    dialogsectorsetup.cpp \
    dialogtextconsole.cpp

HEADERS  += mainwindow.h \
    consolecommands.h \
    atcdialog.h \
    atcmousehandler.h \
    dialogmainmenu.h \
    dialogsectorsetup.h \
    dialogtextconsole.h

FORMS    += mainwindow.ui \
    atcdialog.ui \
    dialogmainmenu.ui \
    dialogsectorsetup.ui \
    dialogtextconsole.ui
