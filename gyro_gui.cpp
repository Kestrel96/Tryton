#include "gyro_gui.h"
#include "ui_gyro_gui.h"

Gyro_Gui::Gyro_Gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gyro_Gui)
{
    ui->setupUi(this);
}

Gyro_Gui::~Gyro_Gui()
{
    delete ui;
}
