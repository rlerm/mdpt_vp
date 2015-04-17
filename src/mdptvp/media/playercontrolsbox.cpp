#include "playercontrolsbox.h"
#include "ui_playercontrolsbox.h"

#include <QtCore/QDebug>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>

#include <vlc-qt/Enums.h>
#include <vlc-qt/MediaPlayer.h>

#include "mdptvp/gui/displaylistmodel.h"
#include "mdptvp/gui/util.h"
#include "mdptvp/media/playercore.h"
#include "mdptvp/media/videowidget.h"

using ::mdptvp::gui::DisplayListModel;
using ::mdptvp::media::PlayerControlsBox;

const char* PlayerControlsBox::PLAY_PAUSE_ICON = ":/icons/play";
const char* PlayerControlsBox::STOP_ICON = ":/icons/stop";

PlayerControlsBox::PlayerControlsBox(QWidget *parent)
    : QGroupBox(parent),
      ui(new Ui::PlayerControlsBox),
      play_pause_action_(
          new QAction(QIcon(PLAY_PAUSE_ICON), tr("Play/Pause"), this)),
      stop_action_(new QAction(QIcon(STOP_ICON), tr("Stop"), this))
{
  ui->setupUi(this);

  play_pause_action_->setCheckable(true);

  DisplayListModel *display_list = new DisplayListModel(ui->monitores_box_);
  ui->monitores_box_->setModel(display_list);
}

PlayerControlsBox::~PlayerControlsBox() {
}

void PlayerControlsBox::setEngine(PlayerCore *engine) {
  engine_ = engine;

  // Synchronize the engine's play/pause status with the UI.
  QObject::connect(engine_->player(), &VlcMediaPlayer::stateChanged, this,
                   &PlayerControlsBox::updateEngineState);

  // Connect the play/pause controls.
  QObject::connect(ui->playPauseButton, &QPushButton::clicked, this,
                   &PlayerControlsBox::playPauseVideo);
  QObject::connect(play_pause_action_, &QAction::triggered, this,
                   &PlayerControlsBox::playPauseVideo);

  // Make the stop button work.
  QObject::connect(ui->stopButton, &QPushButton::clicked, engine_->player(),
                   &VlcMediaPlayer::stop);
  QObject::connect(stop_action_, &QAction::triggered, engine_->player(),
                   &VlcMediaPlayer::stop);

  // "Hide output" button.
  ui->hideOutputButton->setChecked(!engine_->videoOutput()->isVisible());
  connect(ui->hideOutputButton, &QPushButton::clicked,
          [this](bool checked) { setOutputVisibility(!checked); });
  QObject::connect(engine_->videoOutput(), &VideoWidget::visibilityChanged,
                   this, &PlayerControlsBox::setOutputVisibility);

  // "Output fullscreen" button.
  ui->toggleFullscreenButton->setChecked(
      engine_->videoOutput()->isFullScreen());
  QObject::connect(ui->toggleFullscreenButton, &QPushButton::clicked, this,
                   &PlayerControlsBox::setOutputFullscreen);

  // Connect the display selection combo box.
  connect(ui->monitores_box_,
          (void (QComboBox::*)(int)) & QComboBox::currentIndexChanged,
          [this](int new_screen) {
    gui::moveToScreen(engine_->videoOutput(), new_screen);
  });
}

void PlayerControlsBox::playPauseVideo(bool should_play) {
  if (should_play) {
    engine_->player()->play();
  } else {
    engine_->player()->pause();
  }

  updateEngineState();
}

void PlayerControlsBox::setOutputVisibility(bool visible) {
  if (visible) {
    engine_->videoOutput()->show();
  } else {
    engine_->videoOutput()->hide();
  }

  if (visible != !ui->hideOutputButton->isChecked()) {
    ui->hideOutputButton->setChecked(!visible);
  }
}

void PlayerControlsBox::setOutputFullscreen(bool fullscreen) {
  if (ui->toggleFullscreenButton->isChecked() != fullscreen) {
    ui->toggleFullscreenButton->setChecked(fullscreen);
  }

  Qt::WindowStates states = engine_->videoOutput()->windowState();
  if (fullscreen) {
    states |= Qt::WindowFullScreen;
  } else {
    states = states & ~Qt::WindowFullScreen;
  }
  engine_->videoOutput()->setWindowState(states);

  Q_ASSERT(engine_->videoOutput()->isFullScreen() == fullscreen);
}

void PlayerControlsBox::updateEngineState() {
  bool playing = engine_->player()->state() == Vlc::State::Playing;
  ui->playPauseButton->setChecked(playing);
  play_pause_action_->setChecked(playing);
}

QAction *PlayerControlsBox::playPauseAction() {
  return play_pause_action_;
}

QAction *PlayerControlsBox::stopAction() {
  return stop_action_;
}
