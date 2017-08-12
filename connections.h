#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <QObject>
#include <QString>
#include<QCoreApplication>
#include<SFML/Network.hpp>


using namespace std;
using namespace sf;


class connections : public QObject
{
    Q_OBJECT
public:
    explicit connections(QObject *parent = 0);

    int X=0;
    int Y=0;
    int Z=0;
    int R=0;

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
    void ReceivePacket(UdpSocket &socket, sf::Packet &packet, IpAddress Ip, unsigned short port);
    void BindSocket(sf::UdpSocket &socket);
    int SetX(int x);
    int SetY(int y);
    int SetZ(int z);
    int SetR(int r);


};

#endif // CONNECTIONS_H
