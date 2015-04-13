#include "mdptvp/media/playercore.h"

#include <Qt>
#include <QDebug>
#include <QStringList>

#include "mdptvp/filelist/filelist.h"
#include "mdptvp/media/videowidget.h"

using mdptvp::filelist::FileList;
using mdptvp::media::PlayerCore;
using mdptvp::media::VideoWidget;

PlayerCore::PlayerCore(QObject *parent) : QObject(parent) {
#ifndef NDEBUG
  QStringList args;
#else
  QStringList args = QStringList() << "--verbose=1";
  qDebug() << "Initializing vlc-qt " << args;
#endif

  instance_ = new VlcInstance(args, this);
  player_ = new VlcMediaPlayer(instance_);
  video_output_ = new VideoWidget(nullptr);

  player_->setVideoWidget(video_output_);
  // video_output_->setWindowFlags(Qt::FramelessWindowHint);
}

PlayerCore::~PlayerCore() { delete video_output_; }

VlcMediaPlayer *PlayerCore::player() const { return player_; }

QWidget *PlayerCore::videoOutput() const { return video_output_; }

FileList *PlayerCore::newFileList(QObject *parent) {
  return new FileList(parent, instance_);
}

void PlayerCore::playMedia(VlcMedia *media) {
  player_->open(media);
}
