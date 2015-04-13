#ifndef MDPTVP_MEDIA_MEDIAINFOBOX_H_INCLUDED
#define MDPTVP_MEDIA_MEDIAINFOBOX_H_INCLUDED

#include <QGroupBox>

class VlcMediaPlayer;

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
};

}  // namespace media
}  // namespace mdptvp
#endif  // MDPTVP_MEDIA_MEDIAINFOBOX_H_INCLUDED
