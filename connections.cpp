#include "connections.h"

#include <QObject>
#include <QString>
#include<QCoreApplication>
#include<SFML/Network.hpp>
#include<QDebug>

using namespace std;
using namespace sf;

//
connections::connections(QObject *parent) : QObject(parent)
{
    this->ReceiveIp="10.42.0.42";/*sf::IpAddress::getLocalAddress();*/
    this->SendIp="10.42.0.42";
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

//    socket.receive(this->ReceiveData,this->ReceiveIp,this->ReceivePort);
    //int x=22;
    //int y=44;
    double Yaw=0;
    double Pitch=0;
    double Roll=0;

    socket.receive(packet,Ip,port);
    packet>>Yaw>>Pitch>>Roll;
//    emit XReceived(x);
//    emit YReceived(y);
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

