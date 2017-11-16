#ifndef PID_GUI_H
#define PID_GUI_H

#include <QDialog>

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


    double setpoint;
    double CV;
    double offset;

    int throttle;
    int throttle_limit;
    int throttle_lock;


private:
    Ui::PID_GUI *ui;

public slots:

        void DebugInfo();

private slots:

    void Set_Throttle_Lock();
    void Confirm();
    void Set_Is_Open();


};

#endif // PID_GUI_H
