#include "playercontrolsbox.h"
#include "ui_playercontrolsbox.h"

namespace mdptvp {
namespace media {

PlayerControlsBox::PlayerControlsBox(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::PlayerControlsBox)
{
    ui->setupUi(this);
}

PlayerControlsBox::~PlayerControlsBox()
{
    delete ui;
}

void PlayerControlsBox::on_playPauseButton_clicked(bool checked)
{
    emit setPlayState(checked);
}

void PlayerControlsBox::stopMedia()
{
    ui->playPauseButton->setChecked(false);
}

void PlayerControlsBox::mediaPlaying()
{
    ui->playPauseButton->setChecked(true);
}

void PlayerControlsBox::on_stopButton_clicked()
{
    emit stopRequested();
}

void PlayerControlsBox::on_hideOutputButton_clicked(bool checked)
{
    emit outputVisibilityChanged(checked);
}

void PlayerControlsBox::on_toggleFullscreenButton_clicked(bool checked)
{
    emit outputFullScreenChanged(checked);
}

} // namespace media
} // namespace mdptvp
