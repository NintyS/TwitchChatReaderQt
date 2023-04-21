#include "glos.h"
#include "ui_glos.h"

Glos::Glos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Glos)
{
    ui->setupUi(this);
}

Glos::~Glos()
{
    delete ui;
}

float Glos::GetRate() {
    qDebug() << 4;
    return ui->verticalSlider->value();
}

float Glos::GetVolume() {
    qDebug() << 5;
    return ui->verticalSlider_2->value();
}

float Glos::GetPitch() {
    qDebug() << 6;
    return ui->verticalSlider_3->value();
}

void Glos::on_verticalSlider_valueChanged(int value)
{
    qDebug() << 1;
    emit rateChanged();
}


void Glos::on_verticalSlider_2_valueChanged(int value)
{
    qDebug() << 2;
    emit volumeChanged();
}


void Glos::on_verticalSlider_3_valueChanged(int value)
{
    qDebug() << 3;
    emit pitchChanged();
}

