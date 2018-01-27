#include "connections.h"

#include <QObject>
#include <QString>
#include<QCoreApplication>
#include<SFML/Network.hpp>
#include<QDebug>
#include"pid_gui.h"

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
    if(socket.bind(this->ReceivePort)==socket.Done){
         Qstatus="Ready!";
        emit SocketStatus(Qstatus);
    }
    else{
        Qstatus="Not binded!";
        emit SocketStatus(Qstatus);
    }

}


void connections::SendPIDPacket(PID_GUI *PID1, PID_GUI *PID2, PID_GUI *PID3){


    this->SendData<<PID1->Kp<<PID1->Ki<<PID1->Kd<<PID1->tau<<PID1->offset<<PID2->Kp<<PID2->Ki<<PID2->Kd<<PID2->tau<<PID2->offset
                 <<PID3->Kp<<PID3->Ki<<PID3->Kd<<PID3->tau<<PID3->offset;

        this->SendSocket.setBlocking(false);
        this->SendSocket.send(this->SendData,this->ReceiveIp,this->SendPort);
        this->SendData.clear();
}




void connections::SendPacket(){


    this->SendData<<this->X<<this->Y<<this->Z<<this->R;
        this->SendSocket.setBlocking(false);
        this->SendSocket.send(this->SendData,this->ReceiveIp,this->SendPort);
        this->SendData.clear();
        this->X=0;
        this->Y=0;
        this->Z=0;
        this->R=0;
}


void connections::ReceivePacket(UdpSocket &socket, sf::Packet &packet, IpAddress Ip, unsigned short port){

    socket.receive(packet,Ip,port);
    packet>>Yaw>>Pitch>>Roll;

    qDebug()<<"YPR: "<<Yaw<<Pitch<<Roll;
    emit YawRecieved(Yaw);
    emit PitchReceived(Pitch);
    emit RollReceived(Roll);
    packet.clear();

}

int connections::SetX(int x){

    this->X=x;
    return this->X;

}

int connections::SetY(int y){

    this->Y=y;
    return this->Y;
}

int connections::SetZ(int z){

    this->Z=z;
    return this->Z;

}

int connections::SetR(int r){

    this->R=r;
    return this->R;
}
