#include "mdptvp/mainwindow.h"
#include "ui_mainwindow.h"

#include <QObject>

#include <vlc-qt/MediaPlayer.h>
#include <vlc-qt/Media.h>

#include "mdptvp/filelist/filelist.h"
#include "mdptvp/filelist/filelistmodel.h"
#include "mdptvp/media/playercontrolsbox.h"
#include "mdptvp/media/playercore.h"

using mdptvp::MainWindow;
using mdptvp::media::PlayerCore;
using mdptvp::filelist::FileListModel;
using mdptvp::filelist::FileList;
using mdptvp::media::PlayerControlsBox;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      engine_(new PlayerCore(this)) {
  ui->setupUi(this);

  FileListModel *list_model = new FileListModel(ui->playlist_widget_);
  FileList *playlist = engine_->newFileList(list_model);
  list_model->setPlaylist(playlist);
  ui->playlist_widget_->setModel(list_model);

  QObject::connect(playlist, &FileList::fileActivated, engine_,
                   &PlayerCore::playMedia);

  connectSignals();
}

void MainWindow::connectSignals() {
  QObject::connect(engine_->player(), &VlcMediaPlayer::playing,
                   ui->controls_box_, &PlayerControlsBox::mediaPlaying);
  QObject::connect(engine_->player(), &VlcMediaPlayer::stopped,
                   ui->controls_box_, &PlayerControlsBox::stopMedia);

  QObject::connect(ui->controls_box_, &PlayerControlsBox::setPlayState, this,
                   &MainWindow::setPlayState);

  QObject::connect(ui->controls_box_,
                   &PlayerControlsBox::outputVisibilityChanged, this,
                   &MainWindow::setOutputVisibility);

  QObject::connect(ui->controls_box_, &PlayerControlsBox::stopRequested,
                   engine_->player(), &VlcMediaPlayer::stop);
  ui->controls_box_->setOutputVisibility(engine_->videoOutput()->isVisible());

  QObject::connect(ui->controls_box_,
                   &PlayerControlsBox::outputFullScreenChanged, this,
                   &MainWindow::setOutputFullscreen);
  ui->controls_box_->setOutputFullscreen(
      engine_->videoOutput()->isFullScreen());
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::closeEvent(QCloseEvent *) {
  engine_->videoOutput()->close();
}

void MainWindow::setPlayState(bool should_play) {
  if (should_play) {
    engine_->player()->play();
  } else {
    engine_->player()->pause();
  }
}

void MainWindow::setOutputVisibility(bool visible) {
  if (visible) {
    engine_->videoOutput()->show();
  } else {
    engine_->videoOutput()->hide();
  }
}

void MainWindow::setOutputFullscreen(bool fullscreen) {
  Qt::WindowStates states = engine_->videoOutput()->windowState();
  if (fullscreen) {
    states |= Qt::WindowFullScreen;
  } else {
    states = states & ~Qt::WindowFullScreen;
  }
  engine_->videoOutput()->setWindowState(states);
}

