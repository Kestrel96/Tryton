#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"pad.h"
#include"connections.h"
//#include"plot.h"

#include <QObject>
#include<QDesktopWidget>
#include <QWebEngineView>
#include <QGraphicsAnchorLayout>
#include<QCoreApplication>
#include<QTimer>
#include<SFML/Window/Joystick.hpp>
#include<SFML/Network.hpp>
#include<iostream>

using namespace sf;


//sf::UdpSocket UDPsocket;
//sf::Packet Data;
//sf::IpAddress Ip=IpAddress::getLocalAddress();
//unsigned short  port=4567;
int gamepadID;
connections connection;
pad Pad;
int x,y;




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


//    this->resize(screen.availableGeometry(this).size()*0.7);
    //PRZENIESC DO NOWEGO OKNA?
    QWebEngineView *view = new QWebEngineView(this);
    ui->verticalLayout->addWidget(view);
    view->load(QUrl("http://10.42.0.42:8080/?action=stream"));
//    view->show();


//    connect(&Pad,SIGNAL(GamepadConected(int)),ui->PadNo,SLOT(setNum(int)));
//    connect(&Pad,SIGNAL(NoGamepad(QString)),ui->PadNo,SLOT(setText(QString)));
    connect(&Pad,SIGNAL(XAxisValue(int)),ui->x_value,SLOT(setNum(int)));
    connect(&Pad,SIGNAL(YAxisvalue(int)),ui->y_value,SLOT(setNum(int)));
    connect(&Pad,SIGNAL(YawValue(int)),ui->Yaw_value,SLOT(setNum(int)));

//    connect(&Pad,SIGNAL(YawValue(int)),ui->Yaw_value,SLOT(setNum(int)));
//    connect(&Pad,SIGNAL(PitchValue(int)),ui->Pitch_value,SLOT(setNum(int)));
//    connect(&Pad,SIGNAL(RollValue(int)),ui->Roll_value,SLOT(setNum(int)));


    connect(&Pad,SIGNAL(XAxisValue(int)),&connection,SLOT(SetX(int)));
    connect(&Pad,SIGNAL(YAxisvalue(int)),&connection,SLOT(SetY(int)));


//    connect(&connection,SIGNAL(XReceived(int)),ui->LCDX,SLOT(display(int)));
//    connect(&connection,SIGNAL(XReceived(int)),ui->TestXreceived,SLOT(setValue(int)));
//    connect(&connection,SIGNAL(YReceived(int)),ui->LCDY,SLOT(display(int)));
    connect(&connection,SIGNAL(SocketStatus(QString)),ui->SocketStatus,SLOT(setText(QString)));
    connect(&connection,SIGNAL(YawRecieved(double)),ui->Yaw_value,SLOT(setNum(double)));
    connect(&connection,SIGNAL(PitchReceived(double)),ui->Pitch_value,SLOT(setNum(double)));
    connect(&connection,SIGNAL(RollReceived(double)),ui->Roll_value,SLOT(setNum(double)));


    Pad.CheckGamepad(gamepadID);
    this->StartAxesTimer();
    this->StartPadConnectionTimer();
    this->StartReceivingTimer();

}

void MainWindow::StartAxesTimer(){

    QTimer* AxesTimer;
        AxesTimer = new QTimer();
           AxesTimer->setSingleShot(false);
           AxesTimer->start(10);
               connect(AxesTimer, &QTimer::timeout, this, &MainWindow::CheckAxes);

}

void MainWindow::StartPadConnectionTimer(){

    QTimer* ConTimer;
        ConTimer = new QTimer();
           ConTimer->setSingleShot(false);
           ConTimer->start(10);
               connect(ConTimer, &QTimer::timeout, this, &MainWindow::CheckIfConnected);


}

void MainWindow::StartReceivingTimer(){

    QTimer* ReceiveTimer;
        ReceiveTimer = new QTimer();
           ReceiveTimer->setSingleShot(false);
           ReceiveTimer->start(50);
               connect(ReceiveTimer, &QTimer::timeout, this, &MainWindow::ReceivePacket);
               connect(ReceiveTimer, &QTimer::timeout, this, &MainWindow::SendPacket);

    connection.BindSocket(connection.ReceiveSocket);


}

void MainWindow::ReceivePacket(){
    connection.ReceivePacket(connection.ReceiveSocket,connection.ReceiveData,connection.ReceiveIp,connection.ReceivePort);

}

void MainWindow::SendPacket(){
    connection.SendPacket();

}

void MainWindow::CheckIfConnected(){
    Pad.CheckIfStillConnected(gamepadID);
}

void MainWindow::CheckAxes(){
    Pad.XAxis(gamepadID);
    Pad.YAxis(gamepadID);
//to wartosci z trytona
//    Pad.Yaw(gamepadID);
//    Pad.Roll(gamepadID);
//    Pad.Pitch(gamepadID);
}

MainWindow::~MainWindow()
{
    delete ui;
}
