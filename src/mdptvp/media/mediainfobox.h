#ifndef MDPTVP_MEDIA_MEDIAINFOBOX_H_INCLUDED
#define MDPTVP_MEDIA_MEDIAINFOBOX_H_INCLUDED

#include <QGroupBox>
#include <vlc-qt/MediaPlayer.h>

namespace mdptvp {
namespace media {

namespace Ui {
class MediaInfoBox;
}

class MediaInfoBox : public QGroupBox {
  Q_OBJECT

 public:
  explicit MediaInfoBox(QWidget *parent = 0);
  ~MediaInfoBox();
  void setPlayer(VlcMediaPlayer *player);

 private:
  Ui::MediaInfoBox *ui;
  VlcMediaPlayer *player_;

 private slots:
  void updateVolumeLabel(int volume);
  void mediaChanged();
};

}  // namespace media
}  // namespace mdptvp
#endif  // MDPTVP_MEDIA_MEDIAINFOBOX_H_INCLUDED
