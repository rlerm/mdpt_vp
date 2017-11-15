#ifndef MDPTVP_MEDIA_PLAYERCONTROLSBOX_H_INCLUDED
#define MDPTVP_MEDIA_PLAYERCONTROLSBOX_H_INCLUDED

#include <memory>

#include <QGroupBox>
#include <QAction>

#include "mdptvp/media/playercore.h"

namespace mdptvp {
namespace media {

namespace Ui {
class PlayerControlsBox;
} // namespace Ui

class PlayerControlsBox : public QGroupBox {
  Q_OBJECT

 public:
  explicit PlayerControlsBox(QWidget *parent = nullptr);
  ~PlayerControlsBox();

  void setEngine(PlayerCore *engine);

  QAction *playPauseAction();
  QAction *stopAction();

 public slots:
  void setOutputVisibility(bool visible);
  void setOutputFullscreen(bool fullscreen);

 private slots:
   /**
    * Plays or pauses the engine's video.
    * The widgets in this class will have its status reset to reflect the state
    * of the engine after it is played or paused. Note that this state can
    * change quickly: a play or pause request does not happen immediately.
    */
  void playPauseVideo(bool sould_play);

  /**
   * Retrieves the current engine state, and updates related widgets
   * accordingly.
   */
  void updateEngineState();

 private:
  static const char* PLAY_PAUSE_ICON;
  static const char* STOP_ICON;

  std::unique_ptr<Ui::PlayerControlsBox> ui;
  PlayerCore *engine_;
  QAction *play_pause_action_;
  QAction *stop_action_;
};

}  // namespace media
}  // namespace mdptvp

#endif  // MDPTVP_MEDIA_PLAYERCONTROLSBOX_H_INCLUDED
