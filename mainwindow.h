#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void CheckAxes();
    void StartAxesTimer();
    void StartPadConnectionTimer();
    void StartReceivingTimer();
    void StartSendingTimer();
    void CheckIfConnected();
    void ReceivePacket();
    void SendPacket();

private slots:
//    void on_PID_PushButton_clicked();

    void on_PID1_PushButton_clicked();

    void on_PID2_PushButton_clicked();

    void on_PID3_PushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
