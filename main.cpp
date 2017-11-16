#include "mainwindow.h"
#include <QtWebView/QtWebView>
#include <QWebEngineView>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
