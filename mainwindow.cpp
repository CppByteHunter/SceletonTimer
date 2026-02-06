#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer(new QTimer(this))
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , is_started(true)
{
    ui->setupUi(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
    timer->setSingleShot(true);

    audioOutput->setVolume(1.0f);
    player->setAudioOutput(audioOutput);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowSkelet()
{
    auto const ScreenWidth = QGuiApplication::primaryScreen()->geometry().width();
    auto const ScreenHeight = QGuiApplication::primaryScreen()->geometry().height();

    // 1. Создаем диалог
    QPointer<QDialog> dialog(new QDialog);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle("WRAAAAAH");
    dialog->setFixedSize(ScreenWidth/1.5, ScreenHeight/1.5+50); // Фиксированный размер

    // 2. Создаем layout
    QPointer<QVBoxLayout> layout(new QVBoxLayout(dialog));

    // 3. Создаем видео виджет
    QPointer<QVideoWidget> videoWidget(new QVideoWidget(dialog));
    videoWidget->setMinimumSize(ScreenWidth/1.5, ScreenHeight/1.5);
    layout->addWidget(videoWidget);

    // 4. Создаем плеер
    player->setPosition(0);
    player->setVideoOutput(videoWidget);
    player->setSource(QUrl("qrc:/video/skeleton.mp4"));

    // 5. Кнопка закрытия
    QPointer<QPushButton> closeButton;
    if(ui->lineEdit->text().isEmpty()){closeButton = new QPushButton("Закрыть", dialog);}
    else{closeButton = new QPushButton(ui->lineEdit->text(), dialog);}
    layout->addWidget(closeButton);

    // 6. Подключаем
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);
    connect(dialog, &QDialog::finished, [&,this]() {
        player->stop(); // Останавливаем при закрытии
        ui->timeEdit->setEnabled(true);
    });

    connect(player, &QMediaPlayer::mediaStatusChanged, [layout ,this](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) { player->play();
        }
    });

    dialog->show();
    player->play();
}

void MainWindow::TimerSlot()
{
    QTime newTime = time.addSecs(-1);
    time.setHMS(newTime.hour(),newTime.minute(),newTime.second());
    ui->timeLabel->setText(time.toString("hh:mm:ss"));
    if(time.hour()   != 0 ||
       time.minute() != 0 ||
       time.second() != 0){
        timer->start(1000);
    }
    else{
        timer->stop();
        is_started = true;
        ui->timeButton->setText("Старт");
        ShowSkelet();
    }
}

void MainWindow::on_timeButton_clicked()
{
    if(is_started == true)
    {
        is_started = false;
        ui->timeButton->setText("Стоп");
        ui->timeEdit->setEnabled(false);
        time = ui->timeEdit->time();
        ui->timeLabel->setText(time.toString("hh:mm:ss"));
        timer->start(1000);
    }
    else
    {
        is_started = true;
        ui->timeButton->setText("Старт");
        ui->timeEdit->setEnabled(true);
        ui->timeEdit->setTime(time);
        timer->stop();
    }
}

