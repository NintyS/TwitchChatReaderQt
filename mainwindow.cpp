#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    setAttribute(Qt::WA_TranslucentBackground);
//    setWindowFlags(Qt::FramelessWindowHint);

    ui->pushButton->setText(status);

    QList<QVoice> voices = speech.availableVoices();
    if (!voices.isEmpty()) {
        speech.setVoice(voices.first());
    }

    speech.setRate(0.1);
    speech.setVolume(0.1);
    speech.setPitch(0.1);
    speech.setLocale(QLocale::Polish);

    QObject::connect(&receiver, &QProcess::readyReadStandardOutput, [&]() {
        QString output(receiver.readAllStandardOutput());
        QStringList lines = output.split("\n");
        for (int i = 0; i < lines.size(); i++) {
            QString line = lines.at(i);
            if(line != "") {
                if(ping) {
                    sf::SoundBuffer buffer;
                    if(!buffer.loadFromFile(QString(QCoreApplication::applicationDirPath() + "/ping.ogg").toStdString())) {
                        qDebug() << "Nie udało się załadować!";
                    }

                    sf::Sound sound;
                    sound.setBuffer(buffer);
                    sound.play();
                    sf::sleep(sf::seconds(0.8));
                }
                ui->listWidget->addItem(line);
                if(read) {
                    speech.say(line);
                }
            }
        }
    });

    QObject::connect(&receiver, &QProcess::readyReadStandardError, [&]() {
        QString output(receiver.readAllStandardError());
        QStringList lines = output.split("\n");
        for (int i = 0; i < lines.size(); i++) {
            QString line = lines.at(i);
            qDebug() << line;
        }
    });

    QObject::connect(&receiver, &QProcess::errorOccurred, [&]() {
        qDebug() << receiver.error();
        qDebug() << receiver.errorString();
    });

    QObject::connect(&receiver, &QProcess::started, [&]() {
       qDebug() << "Program started!";
    });

    QObject::connect(&receiver, &QProcess::stateChanged, [&]() {
        qDebug() << receiver.state();
    });

}

MainWindow::~MainWindow()
{
    delete okno;
    delete glos;
    delete ui;
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    qDebug() << arg1;
    read = arg1;
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    qDebug() << arg1;
    ping = arg1;
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    qDebug() << arg1;
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << "1";
    if(ui->pushButton->text() == "Start") {
        status = "Stop";

        qDebug() << 2;

        QStringList args;
        args.append(ui->lineEdit->text());

        receiver.start("/" + QCoreApplication::applicationDirPath() + "/TwitchChatReceiver", args);

    } else if(ui->pushButton->text() == "Stop") {
        status = "Start";
        receiver.kill();
        qDebug() << 3;
    }

    ui->pushButton->setText(status);
}


void MainWindow::on_actionUstawienia_triggered()
{
    okno = new Okno;
    glos->setWindowTitle("Ustawienia okna");

//    QObject::connect(okno, &Okno::valueChanged, [&]() {
//        qDebug() << "a";
//        setWindowOpacity(okno->GetOpacity()/100);
//    });

    okno->show();
}


void MainWindow::on_actionUstawienia_2_triggered()
{
    glos = new Glos;
    glos->setWindowTitle("Ustawienia głosu");

    QObject::connect(glos, &Glos::rateChanged, [&]() {
        qDebug() << glos->GetRate()/100;
        speech.setRate(glos->GetRate()/100);
    });

    QObject::connect(glos, &Glos::volumeChanged, [&]() {
        qDebug() << glos->GetVolume()/100;
        speech.setVolume(glos->GetVolume()/100);
    });

    QObject::connect(glos, &Glos::pitchChanged, [&]() {
        qDebug() << glos->GetPitch()/100;
        speech.setPitch(glos->GetPitch()/100);
    });

    glos->show();
}

