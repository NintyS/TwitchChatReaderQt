#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QProcess>
#include <QMainWindow>
#include <QTextToSpeech>
#include <SFML/Audio.hpp>
#include <QGraphicsOpacityEffect>

#include "okno.h"
#include "glos.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_actionUstawienia_triggered();

    void on_actionUstawienia_2_triggered();

private:
    Ui::MainWindow *ui;
    QTextToSpeech speech;

    bool read = false;
    bool ping = false;

    QString status = "Start";

    QProcess receiver;

    // Windows:
    Okno *okno;
    Glos *glos;



    //TwitchChatReceiver
};
#endif // MAINWINDOW_H
