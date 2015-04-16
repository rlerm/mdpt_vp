#ifndef MDPTVP_MEDIA_PLAYERCONTROLSBOX_H_INCLUDED
#define MDPTVP_MEDIA_PLAYERCONTROLSBOX_H_INCLUDED

#include <QGroupBox>

class QAction;

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

  QAction *playPauseAction();
  QAction *stopAction();

 public slots:
  void setPlayState(bool playing);
  void stopMedia();
  void mediaPlaying();
  void setOutputVisibility(bool visible);
  void setOutputFullscreen(bool fullscreen);

 signals:
  void playStateChanged(bool shouldPlay);
  void stopRequested();
  void outputVisibilityChanged(bool visible);
  void outputFullScreenChanged(bool fullscreen);
  void moveToScreen(int screen_number);

 private:
  static const char* PLAY_PAUSE_ICON;
  static const char* STOP_ICON;

  Ui::PlayerControlsBox *ui;
  QAction *play_pause_action_;
  QAction *stop_action_;
};

}  // namespace media
}  // namespace mdptvp

#endif  // MDPTVP_MEDIA_PLAYERCONTROLSBOX_H_INCLUDED
