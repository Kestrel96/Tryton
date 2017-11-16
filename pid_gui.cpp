#include "pid_gui.h"
#include "ui_pid_gui.h"

#include<QDebug>

PID_GUI::PID_GUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PID_GUI)
{

    this->Kp=0;
    this->Ki=0;
    this->Kd=0;
    this->tau=1;
    this->setpoint=0;
    this->offset=0;
    //% mocy jaka dajemy do dyspozycji pilotowi
    this->throttle_limit=65;

    ui->setupUi(this);
    this->is_open=0;

    connect(ui->Close_PB,SIGNAL(clicked(bool)),this,SLOT(Set_Is_Open()));
    connect(ui->SetAndClose_PB,SIGNAL(clicked(bool)),this,SLOT(Set_Is_Open()));
    connect(ui->Set_PB,SIGNAL(clicked(bool)),this,SLOT(Confirm()));
    connect(ui->SetAndClose_PB,SIGNAL(clicked(bool)),this,SLOT(Confirm()));

}



void PID_GUI::Confirm(){
    this->Kp=ui->Kp_SpinBox->value();
    this->Ki=ui->Ki_SpinBox->value();
    this->Kd=ui->Kd_SpinBox->value();
    this->tau=ui->tau_SpinBox->value();

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

