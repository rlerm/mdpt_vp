#include "mediainfobox.h"
#include "ui_mediainfobox.h"

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QFileInfo>

#include <vlc-qt/Audio.h>
#include <vlc-qt/Media.h>
#include <vlc-qt/MediaPlayer.h>
#include <vlc-qt/MetaManager.h>

#include "mdptvp/util/text.h"

namespace text_util = mdptvp::util;
using ::mdptvp::media::MediaInfoBox;
class libvlc_media_t;

MediaInfoBox::MediaInfoBox(QWidget *parent)
    : QGroupBox(parent), ui(new Ui::MediaInfoBox) {
  ui->setupUi(this);

  updateVolumeLabel(ui->volume_widget_->volume());
  QObject::connect(ui->volume_widget_, &VlcWidgetVolumeSlider::newVolume, this,
                   &MediaInfoBox::updateVolumeLabel);
}

MediaInfoBox::~MediaInfoBox() {
  delete ui;
}

void MediaInfoBox::setPlayer(VlcMediaPlayer *player) {
    ui->seek_widget_->setMediaPlayer(player);
    ui->volume_widget_->setMediaPlayer(player);

    player->audio()->setVolume(ui->volume_widget_->volume());
    connect(ui->volume_widget_, &VlcWidgetVolumeSlider::newVolume,
            [player](int volume) { player->audio()->setVolume(volume); });

    connect(player, &VlcMediaPlayer::playing,
                     [this] { mediaChanged(); });

    player_ = player;
}

void MediaInfoBox::updateVolumeLabel(int volume) {
    ui->volume_display_->setText(QString("%1%").arg(volume, 3));
}

void MediaInfoBox::mediaChanged() {
    VlcMedia *media = player_->currentMedia();

    QFileInfo file_info(media->currentLocation());
    qDebug() << "Opened file " << media->currentLocation();

    ui->filename_display_->setText(file_info.fileName());
    ui->size_display_->setText(text_util::formatBytes(file_info.size()));

    VlcMetaManager meta(media);
    ui->title_display_->setText(meta.title());
    // ui->length_display_->setText(QString::number(player_->length()));
    ui->length_display_->setText(
        text_util::formatTime(player_->length()));
}
