#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>
#include <QFileInfo>

namespace mdptvp {
namespace media {

class MediaPlayer : public QObject
{
    Q_OBJECT

public:
    MediaPlayer(QObject* parent = nullptr);

    bool isPlaying();
    int volume();

public slots:
    /**
     * Sets the given file path as the next file to be played.
     */
    void selectFile(const QString &path);

    /**
     * Clear the selected next file.
     */
    void clearSelection();

    /**
     * Stop the current playing media (if any), and start playing the
     * specified file, if it exists.
     */
    void playFile(const QString &path);

    void playPause(bool shouldPlay);

    /**
     * Stops and closes the current media item being played.
     */
    void stop();

    void setVolume(int volume);

    /**
     * Shows or hides the output window.
     */
    void setOutputVisible(bool state);

signals:
    void playerStateChanged(bool state);
    void volumeChanged(int volume);
    void mediaUnloaded();
    void outputVisibilityChanged(bool visible);

private:
    QFileInfo selectedFile;
    bool selectedFileValid;
};

}
}

#endif // MEDIAPLAYER_H
