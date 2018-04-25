#ifndef GYRO_GUI_H
#define GYRO_GUI_H

#include <QDialog>

namespace Ui {
class Gyro_Gui;
}

class Gyro_Gui : public QDialog
{
    Q_OBJECT

public:
    explicit Gyro_Gui(QWidget *parent = 0);
    ~Gyro_Gui();

private:
    Ui::Gyro_Gui *ui;
};

#endif // GYRO_GUI_H
