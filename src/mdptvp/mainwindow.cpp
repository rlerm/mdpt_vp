#include "mdptvp/mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QObject>
#include <QtWidgets/QAction>

#include <vlc-qt/Media.h>
#include <vlc-qt/MediaPlayer.h>

#include "mdptvp/filelist/filelist.h"
#include "mdptvp/filelist/filelistmodel.h"
#include "mdptvp/gui/aboutdialog.h"
#include "mdptvp/media/playercontrolsbox.h"
#include "mdptvp/media/playercore.h"
#include "mdptvp/media/videowidget.h"

using mdptvp::MainWindow;
using mdptvp::filelist::FileList;
using mdptvp::filelist::FileListModel;
using mdptvp::gui::AboutDialog;
using mdptvp::media::PlayerControlsBox;
using mdptvp::media::PlayerCore;
using mdptvp::media::VideoWidget;

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

  ui->info_box_->setPlayer(engine_->player());

  ui->controls_box_->setEngine(engine_);
  ui->controls_box_->setOutputVisibility(true);
  // ui->controls_box_->setOutputFullscreen(true);

  ui->main_toolbar_->addAction(ui->playlist_widget_->getAddFileAction());
  ui->main_toolbar_->addAction(ui->playlist_widget_->getRemoveFileAction());

  ui->controls_toolbar_->addAction(ui->controls_box_->playPauseAction());
  ui->controls_toolbar_->addAction(ui->controls_box_->stopAction());

  connect(ui->action_about_, &QAction::triggered, [this](bool) {
    std::unique_ptr<AboutDialog> about(new AboutDialog);
    about->exec();
  });
}

MainWindow::~MainWindow() {
}

void MainWindow::closeEvent(QCloseEvent *) {
  engine_->videoOutput()->close();
}
