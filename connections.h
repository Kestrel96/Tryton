#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <QObject>
#include <QString>
#include<QCoreApplication>
#include<SFML/Network.hpp>
#include "pid_gui.h"


using namespace std;
using namespace sf;


class connections : public QObject
{
    Q_OBJECT
public:
    explicit connections(QObject *parent = 0);


    double X=0;
    double Y=0;
    double Z=0;
    double R=0;

    double Yaw;
    double Pitch;
    double Roll;

    int ReX=12;
    int ReY=11;
    string Command="nan";

    sf::UdpSocket ReceiveSocket;
    sf::UdpSocket SendSocket;
    sf::Packet SendData;
    sf::Packet ReceiveData;

    sf::IpAddress ReceiveIp;
    sf::IpAddress SendIp;
    unsigned short  SendPort;
    unsigned short ReceivePort=4567;


signals:

    QString SocketStatus(QString);
    int XReceived(int);
    int YReceived(int);
    int YawRecieved(double);
    int PitchReceived(double);
    int RollReceived(double);



public slots:

    void SendPacket();
    void SendPIDPacket(PID_GUI *PID1, PID_GUI *PID2, PID_GUI *PID3);
    void ReceivePacket(UdpSocket &socket, sf::Packet &packet, IpAddress Ip, unsigned short port);
    void BindSocket(sf::UdpSocket &socket);
    int SetX(int x);
    int SetY(int y);
    int SetZ(int z);
    int SetR(int r);


};

#endif // CONNECTIONS_H
