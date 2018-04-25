#include "pid_gui.h"
#include "ui_pid_gui.h"
#include "qcustomplot.h"

#include<QDebug>

PID_GUI::PID_GUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PID_GUI)
{

    this->Kp=0;
    this->Ki=0;
    this->Kd=0;
    this->tau=1;
    this->SP=0;
    this->offset=0;
    TimeStamp=0;

    //% mocy jaka dajemy do dyspozycji pilotowi
    this->throttle_limit=65;

    ui->setupUi(this);
    this->is_open=0;

    ui->Plot->addGraph();
    ui->Plot->addGraph();
    ui->Plot->addGraph();

    ui->Plot->graph(0)->setPen(QPen(Qt::blue));
    ui->Plot->graph(1)->setPen(QPen(Qt::red));
    ui->Plot->graph(2)->setPen(QPen(Qt::green));

    ui->Plot->yAxis->setRange(-110, 110);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->Plot->xAxis->setTicker(timeTicker);


    connect(ui->Close_PB,SIGNAL(clicked(bool)),this,SLOT(Set_Is_Open()));
    connect(ui->SetAndClose_PB,SIGNAL(clicked(bool)),this,SLOT(Set_Is_Open()));
    connect(ui->Set_PB,SIGNAL(clicked(bool)),this,SLOT(Confirm()));
    connect(ui->SetAndClose_PB,SIGNAL(clicked(bool)),this,SLOT(Confirm()));
    connect(this,SIGNAL(DataReady()),this,SLOT(Draw()));



}

void PID_GUI::PreparePacket(){

    Packet.Kd=Kd;
    Packet.Kp=Kp;
    Packet.Ki=Ki;
    Packet.tau=tau;
}


void PID_GUI::Confirm(){
    this->Kp=ui->Kp_SpinBox->value();
    this->Ki=ui->Ki_SpinBox->value();
    this->Kd=ui->Kd_SpinBox->value();
    this->tau=ui->tau_SpinBox->value();
    PreparePacket();

}


PID_GUI::~PID_GUI()
{
    delete ui;
}

void PID_GUI::Set_Is_Open(){

    this->is_open=0;

}

void PID_GUI::Set_Throttle_Lock(){


}

void PID_GUI::DebugInfo(){
    if(this->is_open==1){
    qDebug()<<"Kp,Ki,Kd,dt"<<this->Kp<<this->Ki<<this->Kd<<this->tau;
    }
}

void PID_GUI::SetData(double sp, double cv, double pv, double tStamp){
    SP=sp;
    CV=cv;
    PV=pv;
    TimeStamp=tStamp;
    emit DataReady();

}

void PID_GUI::Draw(){
    //SP
    ui->Plot->graph(0)->addData(TimeStamp,SP);
    //CV
    ui->Plot->graph(1)->addData(TimeStamp,CV);
    //PV
    ui->Plot->graph(2)->addData(TimeStamp,PV);

    ui->Plot->xAxis->setRange(TimeStamp, 1000, Qt::AlignCenter);
    ui->Plot->replot();


}
