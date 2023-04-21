#ifndef GLOS_H
#define GLOS_H

#include <QWidget>

namespace Ui {
    class Glos;
}

class Glos : public QWidget
{
    Q_OBJECT

public:
    explicit Glos(QWidget *parent = nullptr);
    ~Glos();

    float GetRate();
    float GetVolume();
    float GetPitch();

signals:
    void rateChanged();
    void volumeChanged();
    void pitchChanged();

private slots:
    void on_verticalSlider_valueChanged(int value);

    void on_verticalSlider_2_valueChanged(int value);

    void on_verticalSlider_3_valueChanged(int value);

private:
    Ui::Glos *ui;
};

#endif // GLOS_H
