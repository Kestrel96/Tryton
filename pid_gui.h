#ifndef PID_GUI_H
#define PID_GUI_H

#include <QDialog>


struct PID_Packet{

    double Kp;
    double Kd;
    double Ki;
    double tau;

    double offset;
};



namespace Ui {
class PID_GUI;
}

class PID_GUI : public QDialog
{
    Q_OBJECT

public:
    explicit PID_GUI(QWidget *parent = 0);
    bool is_open;
    ~PID_GUI();

    double Kp;
    double Kd;
    double Ki;
    double tau;

    PID_Packet Packet;


    double offset;

    int throttle;
    int throttle_limit;
    int throttle_lock;

    void SetData(double sp, double cv, double pv, double tStamp);

private:
    Ui::PID_GUI *ui;
    void PreparePacket();
    double TimeStamp;
    double SP;
    double CV;
    double PV;
//    double CV_val;
//    double PV_val;
//    double SP_val;

public slots:

        void DebugInfo();

private slots:

    void Set_Throttle_Lock();
    void Confirm();
    void Set_Is_Open();
    void Draw();

signals:
    void DataReady();
};

#endif // PID_GUI_H
