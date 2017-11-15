#ifndef MDPTVP_MEDIA_PLAYERCORE_H_INCLUDED
#define MDPTVP_MEDIA_PLAYERCORE_H_INCLUDED

#include <QObject>

#include <vlc-qt/Instance.h>
#include <vlc-qt/MediaPlayer.h>
#include <vlc-qt/Media.h>

#include "mdptvp/filelist/filelist.h"
#include "mdptvp/media/videowidget.h"

namespace mdptvp {
namespace media {

class PlayerCore : public QObject {
  Q_OBJECT

 public:
  PlayerCore(QObject *parent);
  ~PlayerCore();

  VlcMediaPlayer *player() const;
  VideoWidget *videoOutput() const;
  filelist::FileList *newFileList(QObject *parent = nullptr);

 public slots:
  void playMedia(VlcMedia *media);

 private:
  VlcInstance *instance_;
  VlcMediaPlayer *player_;
  VideoWidget *video_output_;
};

}  // namespace media
}  // namespace mdptvp

#endif  // MDPTVP_MEDIA_PLAYERCORE_H_INCLUDED
