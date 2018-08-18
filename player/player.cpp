#include "player.h"
#include "ui_player.h"


const qreal kVolumeInterval = 0.04;

using namespace QtAV;


player::player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::player)
{
    ui->setupUi(this);

    m_unit = 1000;
    mpPlayer = new AVPlayer(this);
    m_vo = new VideoOutput(this);
    if (!m_vo->widget()) {
//        QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
        return;
    }
    ui->av->addWidget(m_vo->widget());

    mpPlayer->setRenderer(m_vo);
    connect(ui->sick, SIGNAL(sliderMoved(int)), SLOT(seekBySlider(int)));
    connect(ui->sick, SIGNAL(sliderPressed()), SLOT(seekBySlider()));
    connect(ui->volum, SIGNAL(sliderPressed()), SLOT(setVolume()));
    connect(ui->volum, SIGNAL(valueChanged(int)), SLOT(setVolume()));
    connect(mpPlayer, SIGNAL(started()), this, SLOT(onStartPlay()));
    connect(ui->stop, SIGNAL(clicked()), mpPlayer, SLOT(stop()));

}

player::~player()
{
    delete ui;
}

void player::onStartPlay()
{
    ui->end->setText(QTime(0, 0, 0).addMSecs(mpPlayer->mediaStopPosition()).toString(QString::fromLatin1("HH:mm:ss")));
}

void player::on_open_clicked()
{
    QString file = QFileDialog::getOpenFileName(nullptr, tr("Open a video"));
    if (file.isEmpty())
        return;
    mpPlayer->play(file);
}

void player::on_playpause_clicked()
{
    if (!mpPlayer->isPlaying()) {
        mpPlayer->play();
        return;
    }
    mpPlayer->pause(!mpPlayer->isPaused());
}

void player::updateSlider(qint64 value)
{
    ui->sick->setRange(0, int(mpPlayer->duration()/m_unit));
    ui->sick->setValue(int(value/m_unit));
}

void player::updateSlider()
{
    updateSlider(mpPlayer->position());
}

void player::updateSliderUnit()
{
    m_unit = mpPlayer->notifyInterval();
    updateSlider();
}

void player::seekBySlider(int value)
{
    if (!mpPlayer->isPlaying())
        return;
    mpPlayer->seek(qint64(value*m_unit));
}

void player::seekBySlider()
{
    seekBySlider(ui->sick->value());
}

void player::setVolume()
{
    AudioOutput *ao = mpPlayer ? mpPlayer->audio() : nullptr;
    qreal v = qreal(ui->volum->value())*kVolumeInterval;
    if (ao) {
        if (qAbs(int(ao->volume()/kVolumeInterval) - ui->volum->value()) >= int(0.1/kVolumeInterval)) {
            ao->setVolume(v);
        }
    }
    ui->volum->setToolTip(QString::number(v));
}

void player::on_forward_clicked()
{
    mpPlayer->seekForward();
}

void player::on_backward_clicked()
{
    mpPlayer->seekBackward();
}
