#ifndef MDPTVP_MEDIA_PLAYERCORE_H_INCLUDED
#define MDPTVP_MEDIA_PLAYERCORE_H_INCLUDED

#include <QObject>

#include <vlc-qt/Instance.h>
#include <vlc-qt/MediaPlayer.h>
// #include <vlc-qt/WidgetVideo.h>

class VlcMedia;

namespace mdptvp {

namespace filelist {
class FileList;
}  // namespace filelist

namespace media {

using ::mdptvp::filelist::FileList;
class VideoWidget;

class PlayerCore : public QObject {
  Q_OBJECT

 public:
  PlayerCore(QObject *parent);
  ~PlayerCore();

  VlcMediaPlayer *player() const;
  QWidget *videoOutput() const;
  FileList *newFileList(QObject *parent = nullptr);

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
