#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T19:35:12
#
#-------------------------------------------------

QT       += core gui positioning

VPATH += ./atc \
    ./dialog \
    ./ui

INCLUDEPATH += ./atc \
    ./dialog \
    ./ui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ATCConsole
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    atcdialog.cpp \
    dialogmainmenu.cpp \
    dialogsectorsetup.cpp \
    dialogtextconsole.cpp \
    atclineedit.cpp \
    atcbuttons.cpp \
    atcconsolecommands.cpp \
    atcsituationaldisplay.cpp \
    atcairspacefix.cpp \
    atcairspacesector.cpp \
    atcairspace.cpp

HEADERS  += mainwindow.h \
    atcdialog.h \
    atcmousehandler.h \
    dialogmainmenu.h \
    dialogsectorsetup.h \
    dialogtextconsole.h \
    atclineedit.h \
    atcbuttons.h \
    atcconsolecommands.h \
    atcsituationaldisplay.h \
    atcflags.h \
    atcairspacefix.h \
    atcairspacesector.h \
    atcairspace.h

FORMS    += mainwindow.ui \
    atcdialog.ui \
    dialogmainmenu.ui \
    dialogsectorsetup.ui \
    dialogtextconsole.ui
