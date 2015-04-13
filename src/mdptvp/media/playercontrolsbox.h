#ifndef MDPTVP_MEDIA_PLAYERCONTROLSBOX_H_INCLUDED
#define MDPTVP_MEDIA_PLAYERCONTROLSBOX_H_INCLUDED

#include <QGroupBox>

namespace mdptvp {
namespace media {

namespace Ui {
class PlayerControlsBox;
}

class PlayerControlsBox : public QGroupBox {
  Q_OBJECT

 public:
  explicit PlayerControlsBox(QWidget *parent = 0);
  ~PlayerControlsBox();

 public slots:
  void stopMedia();
  void mediaPlaying();
  void setOutputVisibility(bool visible);
  void setOutputFullscreen(bool fullscreen);

 signals:
  void setPlayState(bool shouldPlay);
  void stopRequested();
  void outputVisibilityChanged(bool visible);
  void outputFullScreenChanged(bool fullscreen);
  void moveToScreen(int screen_number);

 private:
  Ui::PlayerControlsBox *ui;
};

}  // namespace media
}  // namespace mdptvp

#endif  // MDPTVP_MEDIA_PLAYERCONTROLSBOX_H_INCLUDED
