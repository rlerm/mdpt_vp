#include "mediainfobox.h"
#include "ui_mediainfobox.h"

#include <QtCore/QObject>
#include <QtCore/QDebug>

#include <vlc-qt/MediaPlayer.h>
#include <vlc-qt/Audio.h>

using ::mdptvp::media::MediaInfoBox;

MediaInfoBox::MediaInfoBox(QWidget *parent)
    : QGroupBox(parent), ui(new Ui::MediaInfoBox) {
  ui->setupUi(this);
}

MediaInfoBox::~MediaInfoBox() {
  delete ui;
}

void MediaInfoBox::setPlayer(VlcMediaPlayer *player) {
    ui->seek_widget_->setMediaPlayer(player);
    ui->volume_widget_->setMediaPlayer(player);

    // ui->volume_widget_->setVolume(player->audio()->volume());
    player->audio()->setVolume(ui->volume_widget_->volume());
    connect(ui->volume_widget_, &VlcWidgetVolumeSlider::newVolume,
            [=](int volume) { player->audio()->setVolume(volume); });

    qDebug() << "Initial audio volume: " << player->audio()->volume();
}
