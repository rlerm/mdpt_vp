#include "mediaplayer.h"

#include <QFileInfo>
#include <QDebug>

using mdptvp::media::MediaPlayer;

MediaPlayer::MediaPlayer(QObject *parent) :
    QObject(parent),
    selectedFileValid(false)
{
}

void MediaPlayer::selectFile(const QString &path) {
    if (path.size() == 0) {
        selectedFileValid = false;
        return;
    }

    selectedFile = path;
    selectedFileValid = true;

    qDebug() << "Selected " << path;
}

void MediaPlayer::playFile(const QString &path)
{

}

void MediaPlayer::playPause(bool shouldPlay)
{
    // TODO: Business and VLC logic here.
    qDebug() << "Play state set to " << shouldPlay;
}

void MediaPlayer::clearSelection() {
    selectedFileValid = false;
}

void MediaPlayer::stop()
{
    // TODO: VLC logic for stopping.
    emit mediaUnloaded();
}

void MediaPlayer::setVolume(int volume)
{

}

void MediaPlayer::setOutputVisible(bool state)
{

}

