#include "mdptvp/media/playercore.h"

#include <QDebug>
#include <QStringList>
#include <Qt>

#include "mdptvp/filelist/filelist.h"
#include "mdptvp/media/videowidget.h"

namespace mdptvp {
namespace media {

using mdptvp::filelist::FileList;

PlayerCore::PlayerCore(QObject *parent) : QObject(parent) {
  QStringList args;
  args << "--intf" << "dummy";

#ifndef NDEBUG
  args << "--verbose=2";
  qDebug() << "Initializing vlc-qt " << args;
#endif

  instance_ = new VlcInstance(args, this);
  player_ = new VlcMediaPlayer(instance_);

  // Initialize the video output widget.
  video_output_ = new VideoWidget(nullptr);

  player_->setVideoWidget(video_output_);
}

PlayerCore::~PlayerCore() {
  delete video_output_;
}

VlcMediaPlayer *PlayerCore::player() const {
  return player_;
}

VideoWidget *PlayerCore::videoOutput() const {
  return video_output_;
}

FileList *PlayerCore::newFileList(QObject *parent) {
  return new FileList(parent, instance_);
}

void PlayerCore::playMedia(VlcMedia *media) {
  player_->open(media);
}

}  // namespace media
}  // namespace mdptvp
