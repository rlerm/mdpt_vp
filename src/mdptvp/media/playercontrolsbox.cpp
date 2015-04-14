#include "playercontrolsbox.h"
#include "ui_playercontrolsbox.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtCore/QDebug>

#include "mdptvp/gui/displaylistmodel.h"

using ::mdptvp::media::PlayerControlsBox;
using ::mdptvp::gui::DisplayListModel;

PlayerControlsBox::PlayerControlsBox(QWidget *parent)
    : QGroupBox(parent), ui(new Ui::PlayerControlsBox) {
  ui->setupUi(this);

  DisplayListModel *display_list = new DisplayListModel(ui->monitores_box_);
  ui->monitores_box_->setModel(display_list);
  QObject::connect(
      ui->monitores_box_,
      (void (QComboBox::*)(int)) & QComboBox::currentIndexChanged, this,
      [this](int screen_number) { emit moveToScreen(screen_number); });

  connect(ui->playPauseButton, &QPushButton::clicked,
          [this](bool checked) { emit setPlayState(checked); });
  connect(ui->stopButton, &QPushButton::clicked,
          [this]() { emit stopRequested(); });
  connect(ui->hideOutputButton, &QPushButton::clicked,
          [this](bool checked) { emit outputVisibilityChanged(!checked); });
  connect(ui->toggleFullscreenButton, &QPushButton::clicked,
          [this](bool checked) { emit outputFullScreenChanged(checked); });
}

PlayerControlsBox::~PlayerControlsBox() {
  delete ui;
}

void PlayerControlsBox::stopMedia() {
  ui->playPauseButton->setChecked(false);
}

void PlayerControlsBox::mediaPlaying() {
  ui->playPauseButton->setChecked(true);
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
