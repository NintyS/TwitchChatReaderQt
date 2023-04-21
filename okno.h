#ifndef OKNO_H
#define OKNO_H

#include <QWidget>

namespace Ui {
class Okno;
}

class Okno : public QWidget
{
    Q_OBJECT

public:
    explicit Okno(QWidget *parent = nullptr);
    ~Okno();

    float GetOpacity();

signals:
    void valueChanged();

private slots:
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::Okno *ui;
};

#endif // OKNO_H
