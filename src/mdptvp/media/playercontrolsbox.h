#ifndef MDPTVP_MEDIA_PLAYERCONTROLSBOX_H
#define MDPTVP_MEDIA_PLAYERCONTROLSBOX_H

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

 private slots:
  void on_playPauseButton_clicked(bool checked);

  void on_stopButton_clicked();

  void on_hideOutputButton_clicked(bool checked);

  void on_toggleFullscreenButton_clicked(bool checked);

 private:
  Ui::PlayerControlsBox *ui;
};

}  // namespace media
}  // namespace mdptvp

#endif  // MDPTVP_MEDIA_PLAYERCONTROLSBOX_H
