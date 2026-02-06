#include "settimer.h"
#include "ui_settimer.h"

SetTimer::SetTimer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetTimer)
{
    ui->setupUi(this);
}

SetTimer::~SetTimer()
{
    delete ui;
}
