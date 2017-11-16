#-------------------------------------------------
#
# Project created by QtCreator 2016-12-28T15:00:32
#
#-------------------------------------------------

QT       += core gui webview webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TrytonGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pad.cpp \
    connections.cpp \
    pid_gui.cpp


HEADERS  += mainwindow.h \
    pad.h \
    connections.h \
    pid_gui.h

FORMS    += mainwindow.ui \
    pid_gui.ui


unix:!macx: LIBS += -L$$PWD/../../SFMLqt/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += $$PWD/../../SFMLqt/include
DEPENDPATH += $$PWD/../../SFMLqt/include

INCLUDEPATH += /home/kuba/Qt/qcustomplot
