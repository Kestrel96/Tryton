#include "connections.h"

#include <QObject>
#include <QString>
#include<QCoreApplication>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<QDebug>
#include"pid_gui.h"

//STEROWANIE OGARNIJ

using namespace std;
using namespace sf;

//
connections::connections(QObject *parent) : QObject(parent)
{
    this->ReceiveIp="10.42.0.14";/*sf::IpAddress::getLocalAddress();*/
    this->SendIp="10.42.0.14";
    this->ReceivePort=4567;
    this->SendPort=1234;

}


void connections::BindSocket(UdpSocket &socket){
    socket.setBlocking(false);
    QString Qstatus;
    if(socket.bind(ReceivePort)==socket.Done){
        Qstatus="Ready!";
        emit SocketStatus(Qstatus);
    }
    else{
        Qstatus="Not binded!";
        emit SocketStatus(Qstatus);
    }

}


void connections::SendPIDPacket(PID_GUI *PID1, PID_GUI *PID2, PID_GUI *PID3){


    this->SendPIDData<<PID1->Kp<<PID1->Ki<<PID1->Kd<<PID2->Kp<<PID2->Ki<<PID2->Kd<<PID3->Kp<<PID3->Ki<<PID3->Kd;

    this->SendSocket.setBlocking(false);
    this->SendSocket.send(this->SendPIDData,this->ReceiveIp,5678);
    this->SendPIDData.clear();
}




void connections::SendPacket(bool Switch, double max_Yaw, double max_Pitch, double max_Roll){

    if(Switch==0){
        Yaw_SP=X*0.01+last_Y_SP;
        //Y;
        //R;
        Roll_SP=Z*0.01+last_R_SP;

        if(Yaw_SP>=max_Yaw){
            Yaw_SP=max_Yaw;
        }

        if(Yaw_SP<=-max_Yaw){
            Yaw_SP=-max_Yaw;
        }

        if(Roll_SP>=max_Roll){
            Roll_SP=max_Roll;
        }
        if(Roll_SP<=-max_Roll){
            Roll_SP=-max_Roll;
        }
        Z=0;
        X=0;


    }
    else{
        //X
        Pitch_SP=Y*0.01+last_P_SP;
        //R

        if(Pitch_SP>=max_Pitch){
            Pitch_SP=max_Pitch;
        }
        if(Pitch_SP<=-max_Pitch){
            Pitch_SP=-max_Pitch;
        }
        Y=0;
        Z=0;


    }

    this->SendData<<Yaw_SP<<Pitch_SP<<Roll_SP<<X<<Y<<R<<Z;
    this->SendSocket.setBlocking(false);
    this->SendSocket.send(this->SendData,this->ReceiveIp,this->SendPort);
    this->SendData.clear();
    emit P_SP(Pitch_SP);
    emit Y_SP(Yaw_SP);
    emit R_SP(Roll_SP);
    this->X=0;
    this->Y=0;
    this->Z=0;
    this->R=0;

    if(Switch==1){
        last_P_SP=Pitch_SP;
    }
    else{
        last_Y_SP=Yaw_SP;
        last_R_SP=Roll_SP;
    }

}


void connections::ReceivePacket(UdpSocket &socket, sf::Packet &packet, IpAddress Ip, unsigned short port){

    socket.receive(packet,Ip,port);
    packet>>Yaw>>Pitch>>Roll>>Yaw_CV>>Pitch_CV>>Roll_CV;

    qDebug()<<"YPR: "<<Yaw<<Pitch<<Roll;
    emit YawRecieved(Yaw);
    emit PitchReceived(Pitch);
    emit RollReceived(Roll);
    packet.clear();

}

int connections::SetX(int x){

    this->X=(double) x;
    return this->X;

}

int connections::SetY(int y){

    this->Y=(double) y;
    return this->Y;
}

int connections::SetZ(int z){

    this->Z=(double)z;
    return this->Z;

}

int connections::SetR(int r){

    this->R=(double)r;
    return this->R;
}
