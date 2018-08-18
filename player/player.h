#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>

#include "../libQtAV/QtAV/QtAV.h"
#include "../libQtAVWidgets/QtAVWidgets/QtAVWidgets.h"

class StatisticsView;


namespace Ui {
class player;
}

class player : public QWidget
{
    Q_OBJECT

public:
    explicit player(QWidget *parent = nullptr);
    ~player();

private slots:
    void on_open_clicked();
    void on_playpause_clicked();

public Q_SLOTS:
    void seekBySlider(int value);
    void seekBySlider();
    void onStartPlay();

private Q_SLOTS:
    void updateSlider(qint64 value);
    void updateSlider();
    void updateSliderUnit();
    void setVolume();
    void on_forward_clicked();
    void on_backward_clicked();

private:
    Ui::player *ui;

    int m_unit;
    QtAV::VideoOutput *m_vo;
    QtAV::AVPlayer *mpPlayer;

};

#endif // PLAYER_H
