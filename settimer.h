#ifndef SETTIMER_H
#define SETTIMER_H

#include <QDialog>

namespace Ui {
class SetTimer;
}

class SetTimer : public QDialog
{
    Q_OBJECT

public:
    explicit SetTimer(QWidget *parent = nullptr);
    ~SetTimer();

private:
    Ui::SetTimer *ui;
};

#endif // SETTIMER_H
