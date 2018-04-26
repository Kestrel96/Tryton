#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"pad.h"
#include"connections.h"
#include"pid_gui.h"

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
PID_GUI *PID1, *PID2, *PID3;
QTime T;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    T.start();
    PID1=new PID_GUI(this);
    PID2=new PID_GUI(this);
    PID3=new PID_GUI(this);




    //    this->resize(screen.availableGeometry(this).size()*0.7);
    //PRZENIESC DO NOWEGO OKNA?
    QWebEngineView *view = new QWebEngineView(this);
    ui->verticalLayout->addWidget(view);
    view->load(QUrl("http://10.42.0.14:8080/?action=stream"));
    //    view->show();



    connect(&Pad,SIGNAL(XAxisValue(int)),ui->x_value,SLOT(setNum(int)));
    connect(&Pad,SIGNAL(YAxisvalue(int)),ui->y_value,SLOT(setNum(int)));
    connect(&Pad,SIGNAL(ZAxisValue(int)),ui->z_value,SLOT(setNum(int)));
    connect(&Pad,SIGNAL(RAxisvalue(int)),ui->r_value,SLOT(setNum(int)));

    connect(&connection,SIGNAL(Y_SP(double)),ui->YAW_SP,SLOT(setNum(double)));
    connect(&connection,SIGNAL(P_SP(double)),ui->PITCH_SP,SLOT(setNum(double)));
    connect(&connection,SIGNAL(R_SP(double)),ui->ROLL_SP,SLOT(setNum(double)));

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
    ConTimer->start(30);
    connect(ConTimer, &QTimer::timeout, this, &MainWindow::CheckIfConnected);



}

void MainWindow::StartReceivingTimer(){

    QTimer* ReceiveTimer;
    ReceiveTimer = new QTimer();
    ReceiveTimer->setSingleShot(false);
    ReceiveTimer->start(15);
    connect(ReceiveTimer, &QTimer::timeout, this, &MainWindow::ReceivePacket);
    //  connect(ReceiveTimer, &QTimer::timeout, this, &MainWindow::SendPacket);

    connection.BindSocket(connection.ReceiveSocket);


}

void MainWindow::StartSendingTimer(){

    QTimer* SendTimer;
    SendTimer = new QTimer();
    SendTimer->setSingleShot(false);
    SendTimer->start(50);
    //  connect(ReceiveTimer, &QTimer::timeout, this, &MainWindow::ReceivePacket);
    connect(SendTimer, &QTimer::timeout, this, &MainWindow::SendPacket);


}

void MainWindow::ReceivePacket(){
    connection.ReceivePacket(connection.ReceiveSocket,connection.ReceiveData,connection.ReceiveIp,connection.ReceivePort);

    PID1->DebugInfo();
    PID2->DebugInfo();
    PID3->DebugInfo();

}

void MainWindow::SendPacket(){
    connection.SendPacket(Pad.SwitchPressed,180,45,45);
    connection.SendPIDPacket(PID1,PID2,PID3);

}

void MainWindow::CheckIfConnected(){
    Pad.CheckIfStillConnected(gamepadID);


}

void MainWindow::CheckAxes(){
    Pad.XAxis(gamepadID);
    Pad.YAxis(gamepadID);
    Pad.ZAxis(gamepadID);
    Pad.RAxis(gamepadID);
    Pad.SwitchIsPressed(gamepadID);

    PID1->SetData(connection.Yaw_SP,connection.Yaw_CV,connection.Yaw,T.elapsed()/10);
    PID2->SetData(connection.Pitch_SP,connection.Pitch_CV,connection.Pitch,T.elapsed()/10);
    PID3->SetData(connection.Roll_SP,connection.Roll_CV,connection.Roll,T.elapsed()/10);





}

MainWindow::~MainWindow()
{
    delete PID1;
    delete PID2;
    delete PID3;
    delete ui;
}

void MainWindow::on_PID1_PushButton_clicked()
{

    if(PID1->is_open==0){
        PID1->show();
        PID1->is_open=1;
        PID1->setModal(true);
    }
}


void MainWindow::on_PID2_PushButton_clicked()
{
    if(PID2->is_open==0){
        PID2->show();
        PID2->is_open=1;
        PID2->setModal(true);
    }

}

void MainWindow::on_PID3_PushButton_clicked()
{

    if(PID3->is_open==0){
        PID3->show();
        PID3->is_open=1;
        PID3->setModal(true);
    }

}

