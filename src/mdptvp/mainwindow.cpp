#include "mdptvp/mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QObject>

#include <vlc-qt/Enums.h>
#include <vlc-qt/Media.h>
#include <vlc-qt/MediaPlayer.h>

#include "mdptvp/filelist/filelist.h"
#include "mdptvp/filelist/filelistmodel.h"
#include "mdptvp/gui/util.h"
#include "mdptvp/media/playercontrolsbox.h"
#include "mdptvp/media/playercore.h"
#include "mdptvp/media/videowidget.h"

using mdptvp::MainWindow;
using mdptvp::media::PlayerCore;
using mdptvp::media::VideoWidget;
using mdptvp::filelist::FileListModel;
using mdptvp::filelist::FileList;
using mdptvp::media::PlayerControlsBox;
namespace gui = mdptvp::gui;

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

  ui->main_toolbar_->addAction(ui->playlist_widget_->getAddFileAction());
  ui->main_toolbar_->addAction(ui->playlist_widget_->getRemoveFileAction());

  ui->controls_toolbar_->addAction(ui->controls_box_->playPauseAction());
  ui->controls_toolbar_->addAction(ui->controls_box_->stopAction());
}

void MainWindow::connectSignals() {
  connect(engine_->player(), &VlcMediaPlayer::stateChanged, [this]() {
    ui->controls_box_->setPlayState(engine_->player()->state() ==
                                    Vlc::State::Playing);
  });

  QObject::connect(ui->controls_box_, &PlayerControlsBox::playStateChanged, this,
                   &MainWindow::setPlayState);

  QObject::connect(ui->controls_box_,
                   &PlayerControlsBox::outputVisibilityChanged, this,
                   &MainWindow::setOutputVisibility);

  QObject::connect(ui->controls_box_, &PlayerControlsBox::stopRequested,
                   engine_->player(), &VlcMediaPlayer::stop);
  ui->controls_box_->setOutputVisibility(engine_->videoOutput()->isVisible());
  connect(ui->controls_box_, &PlayerControlsBox::moveToScreen,
          [=](int new_screen) {
    gui::moveToScreen(engine_->videoOutput(), new_screen);
  });

  QObject::connect(engine_->videoOutput(), &VideoWidget::visibilityChanged,
                   ui->controls_box_,
                   &PlayerControlsBox::setOutputVisibility);

  QObject::connect(ui->controls_box_,
                   &PlayerControlsBox::outputFullScreenChanged, this,
                   &MainWindow::setOutputFullscreen);
  ui->controls_box_->setOutputFullscreen(
      engine_->videoOutput()->isFullScreen());

  ui->info_box_->setPlayer(engine_->player());
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

  ui->controls_box_->setPlayState(engine_->player()->state() ==
                                  Vlc::State::Playing);
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

  Q_ASSERT(engine_->videoOutput()->isFullScreen() == fullscreen);
}

