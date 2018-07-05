#ifndef SORTWINDOW_H
#define SORTWINDOW_H

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
    int algomod;
    static Widget * getInstance();
    void setTitle();

private:
    static Widget *w;
    Ui::Widget *ui;
    void reset();


signals:
    void showmain();
    void changeAlgo();

private slots:
    void receivemain();
    void on_pushButton_8_clicked();

    void on_restart_btn_clicked();
    void on_reset_btn_clicked();
    void on_play_btn_clicked();
    void on_next_btn_clicked();
    void on_random_btn_clicked();

    void on_selection_btn_clicked();
    void on_radix_btn_clicked();
    void on_quick_btn_clicked();
    void on_merge_btn_clicked();
    void on_insertion_btn_clicked();
    void on_heap_btn_clicked();
    void on_bubble_btn_clicked();

};

#endif // SORTWINDOW_H
