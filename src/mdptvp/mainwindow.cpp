#include "mdptvp/mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

#include "mdptvp/media/mediaplayer.h"

namespace mdptvp {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    player(new media::MediaPlayer(this))
{
    ui->setupUi(this);

    // Connect signals from the player to its UI.
    QObject::connect(ui->controlsBox,
                     &media::PlayerControlsBox::setPlayState,
                     player,
                     &media::MediaPlayer::playPause);
    QObject::connect(ui->controlsBox,
                     &media::PlayerControlsBox::outputVisibilityChanged,
                     player,
                     &media::MediaPlayer::setOutputVisible);
    QObject::connect(ui->playList,
                     &FileListWidget::fileActivated,
                     player,
                     &media::MediaPlayer::playFile);
    QObject::connect(ui->playList,
                     &FileListWidget::fileSelected,
                     player,
                     &media::MediaPlayer::selectFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}
}
