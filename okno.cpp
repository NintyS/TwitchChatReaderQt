#include "okno.h"
#include "ui_okno.h"

Okno::Okno(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Okno)
{
    ui->setupUi(this);
}

Okno::~Okno()
{
    delete ui;
}

float Okno::GetOpacity(){
    return ui->horizontalSlider->value();
}


void Okno::on_horizontalSlider_valueChanged(int value)
{
    emit valueChanged();
}

