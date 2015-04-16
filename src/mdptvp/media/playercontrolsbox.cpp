#include "playercontrolsbox.h"
#include "ui_playercontrolsbox.h"

#include <QtCore/QDebug>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>

#include "mdptvp/gui/displaylistmodel.h"

using ::mdptvp::media::PlayerControlsBox;
using ::mdptvp::gui::DisplayListModel;

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
  QObject::connect(
      ui->monitores_box_,
      (void (QComboBox::*)(int)) & QComboBox::currentIndexChanged, this,
      [this](int screen_number) { emit moveToScreen(screen_number); });

  connect(ui->playPauseButton, &QPushButton::clicked,
          [this](bool checked) { emit playStateChanged(checked); });
  connect(ui->stopButton, &QPushButton::clicked,
          [this]() { emit stopRequested(); });
  connect(ui->hideOutputButton, &QPushButton::clicked,
          [this](bool checked) { emit outputVisibilityChanged(!checked); });
  connect(ui->toggleFullscreenButton, &QPushButton::clicked,
          [this](bool checked) { emit outputFullScreenChanged(checked); });

  connect(play_pause_action_, &QAction::triggered,
          [this](bool checked) { emit playStateChanged(checked); });
  connect(stop_action_, &QAction::triggered,
          [this]() { emit stopRequested(); });
}

PlayerControlsBox::~PlayerControlsBox() {
  delete ui;
}

void PlayerControlsBox::stopMedia() {
  setPlayState(false);
}

void PlayerControlsBox::mediaPlaying() {
  setPlayState(true);
}

void PlayerControlsBox::setOutputVisibility(bool visible) {
  qDebug() << "output visibility changed";
  if (visible != !ui->hideOutputButton->isChecked()) {
    ui->hideOutputButton->setChecked(!visible);
  }
}

void PlayerControlsBox::setOutputFullscreen(bool fullscreen) {
  ui->toggleFullscreenButton->setChecked(fullscreen);
}

void PlayerControlsBox::setPlayState(bool playing) {
  ui->playPauseButton->setChecked(playing);
  play_pause_action_->setChecked(playing);
}

QAction *PlayerControlsBox::playPauseAction() {
  return play_pause_action_;
}

QAction *PlayerControlsBox::stopAction() {
  return stop_action_;
}
