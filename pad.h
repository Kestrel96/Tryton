#ifndef PAD_H
#define PAD_H

#include <QObject>
#include<QString>
#include<QCoreApplication>
#include<SFML/Window/Joystick.hpp>
#include<SFML/Network.hpp>

using namespace std;
using namespace sf;

class pad : public QObject
{
    Q_OBJECT

public:
    explicit pad(QObject *parent = 0);
    void CheckGamepad(int &ID);
    void XAxis(int ID);
    void YAxis(int ID);
//    void Yaw(int ID);
//    void Pitch(int ID);
//    void Roll (int ID);

private:

    bool isConnected;

signals:

    int XAxisValue(int);
    int YAxisvalue(int);
    int YawValue (int);
    int PitchValue (int);
    int RollValue(int);

    int GamepadConected(int);
    QString NoGamepad(QString);

public slots:

    void CheckIfStillConnected(int &ID);

};

#endif // PAD_H
