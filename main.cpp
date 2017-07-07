#include "mainwindow.h"
#include <QtWebView/QtWebView>
#include <QWebEngineView>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    QWebEngineView *view = new QWebEngineView();
//    view->load(QUrl("http://www.qt.io/"));
//    view->show();
    w.show();

    return a.exec();
}
