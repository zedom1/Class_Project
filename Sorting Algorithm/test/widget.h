#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIntValidator>
#include "event.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_play_btn_clicked();

    void on_next_btn_clicked();

    void on_restart_btn_clicked();

    void on_random_btn_clicked();

    void on_reset_btn_clicked();

private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
