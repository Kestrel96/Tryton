#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"pad.h"
#include"connections.h"
#include"pid_gui.h"


//#include"plot.h"

#include<QObject>
#include<QDesktopWidget>
#include<QWebEngineView>
#include<QGraphicsAnchorLayout>
#include<QCoreApplication>
#include<QTimer>
#include<SFML/Window/Joystick.hpp>
#include<SFML/Network.hpp>
#include<iostream>

using namespace sf;


int gamepadID;
connections connection;
pad Pad;
PID_GUI *PID;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PID=new PID_GUI(this);


//    this->resize(screen.availableGeometry(this).size()*0.7);
    //PRZENIESC DO NOWEGO OKNA?
    QWebEngineView *view = new QWebEngineView(this);
    ui->verticalLayout->addWidget(view);
    view->load(QUrl("http://10.42.0.14:8080/?action=stream"));
//    view->show();


    //    connect(&Pad,SIGNAL(GamepadConected(int)),ui->PadNo,SLOT(setNum(int)));
    //    connect(&Pad,SIGNAL(NoGamepad(QString)),ui->PadNo,SLOT(setText(QString)));

    connect(&Pad,SIGNAL(XAxisValue(int)),ui->x_value,SLOT(setNum(int)));
    connect(&Pad,SIGNAL(YAxisvalue(int)),ui->y_value,SLOT(setNum(int)));
    connect(&Pad,SIGNAL(ZAxisValue(int)),ui->z_value,SLOT(setNum(int)));
    connect(&Pad,SIGNAL(RAxisvalue(int)),ui->r_value,SLOT(setNum(int)));


    connect(&Pad,SIGNAL(XAxisValue(int)),&connection,SLOT(SetX(int)));
    connect(&Pad,SIGNAL(YAxisvalue(int)),&connection,SLOT(SetY(int)));
    connect(&Pad,SIGNAL(ZAxisValue(int)),&connection,SLOT(SetZ(int)));
    connect(&Pad,SIGNAL(RAxisvalue(int)),&connection,SLOT(SetR(int)));

    connect(&connection,SIGNAL(SocketStatus(QString)),ui->SocketStatus,SLOT(setText(QString)));
    connect(&connection,SIGNAL(YawRecieved(double)),ui->Yaw_value,SLOT(setNum(double)));
    connect(&connection,SIGNAL(PitchReceived(double)),ui->Pitch_value,SLOT(setNum(double)));
    connect(&connection,SIGNAL(RollReceived(double)),ui->Roll_value,SLOT(setNum(double)));


    Pad.CheckGamepad(gamepadID);
    this->StartAxesTimer();
    this->StartPadConnectionTimer();
    this->StartReceivingTimer();
    this->StartSendingTimer();

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
             //  connect(ReceiveTimer, &QTimer::timeout, this, &MainWindow::SendPacket);

    connection.BindSocket(connection.ReceiveSocket);


}

void MainWindow::StartSendingTimer(){

    QTimer* SendTimer;
    SendTimer = new QTimer();
    SendTimer->setSingleShot(false);
    SendTimer->start(40);
    //  connect(ReceiveTimer, &QTimer::timeout, this, &MainWindow::ReceivePacket);
    connect(SendTimer, &QTimer::timeout, this, &MainWindow::SendPacket);


}

void MainWindow::ReceivePacket(){
    connection.ReceivePacket(connection.ReceiveSocket,connection.ReceiveData,connection.ReceiveIp,connection.ReceivePort);
    PID->DebugInfo();

}

void MainWindow::SendPacket(){
    connection.SendPacket();
    connection.SendPIDPacket(PID->Kp,PID->Kd,PID->Ki,PID->tau);

}

void MainWindow::CheckIfConnected(){
    Pad.CheckIfStillConnected(gamepadID);
}

void MainWindow::CheckAxes(){
    Pad.XAxis(gamepadID);
    Pad.YAxis(gamepadID);
    Pad.ZAxis(gamepadID);
    Pad.RAxis(gamepadID);


}

MainWindow::~MainWindow()
{
    delete PID;
    delete ui;
}

void MainWindow::on_PID_PushButton_clicked()
{

    if(PID->is_open==0){
    PID->show();
    PID->is_open=1;
    PID->setModal(true);
    }
}
