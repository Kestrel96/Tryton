#include "pad.h"

#include <QObject>
#include<QCoreApplication>
#include<QString>
#include<SFML/Window/Joystick.hpp>
#include<SFML/Network.hpp>

using namespace sf;
pad::pad(QObject *parent) : QObject(parent)
{
    this->isConnected=0;
}

void pad::CheckIfStillConnected(int &ID){

    QString NotConnected="Controller disconnected!";
    if(!Joystick::isConnected(ID)){
        this->isConnected=0;
        int zero=0;
        Joystick::update();
        emit XAxisValue(zero);
        emit YAxisvalue(zero);
        emit YawValue(zero);
        emit PitchValue(zero);
        emit RollValue(zero);
        emit NoGamepad(NotConnected);
        this->CheckGamepad(ID);
    }

}

void pad::CheckGamepad(int &ID){
    QString NotConnected="Controller disconnected!";
    if(this->isConnected!=1){
        for(int i=0;i<Joystick::Count;i++){
            ID=i;
            Joystick::update();

            if(Joystick::isConnected(i)){
                ID=i;
                this->isConnected=1;
                emit GamepadConected(ID);
                break;
            }
            if(!Joystick::isConnected(i)){

                ID=100;
                this->isConnected=0;
                emit NoGamepad(NotConnected);
                break;
            }
        }
    }

}

void pad::XAxis(int ID){

    int x=0;
    Joystick::update();
    x=Joystick::getAxisPosition(ID,Joystick::Axis::X);
    emit XAxisValue(x);

}



void pad::YAxis(int ID){
    int y=0;
    Joystick::update();
    y=Joystick::getAxisPosition(ID,Joystick::Axis::Y);
    y=-1*y;
    emit YAxisvalue(y);


}

//TO WARTOSCI Z TRYTONA
//void pad::Yaw(int ID){
//    int yaw=0;
//    Joystick::update();
//    yaw=Joystick::getAxisPosition(ID,Joystick::Axis::R);
//    yaw=-1*yaw;
//    emit YawValue(yaw);


//}

//void pad::Pitch(int ID){
//    int pitch=0;
//    Joystick::update();
//    pitch=Joystick::getAxisPosition(ID,Joystick::Axis::U);
//    pitch=-1*pitch;
//    emit PitchValue(pitch);


//}

//void pad::Roll(int ID){
//    int roll=0;
//    Joystick::update();
//    roll=Joystick::getAxisPosition(ID,Joystick::Axis::V);
//    roll=-1*roll;
//    emit RollValue(roll);


//}

