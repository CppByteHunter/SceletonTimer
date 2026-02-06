#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QtMultimediaWidgets>
#include <QtMultimediaWidgets/QVideoWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QMediaPlayer* player;
    QAudioOutput *audioOutput;
    QTime time;
    bool is_started = true;

    void ShowSkelet();

private slots:
    void TimerSlot();
    void on_timeButton_clicked();
};
#endif // MAINWINDOW_H
