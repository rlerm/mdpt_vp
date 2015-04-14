#include "mdptvp/media/videowidget.h"

#include <QPalette>
#include <QDebug>

using ::mdptvp::media::VideoWidget;

VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent) {
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::black));
    setWindowTitle(tr("Saída de vídeo"));
    setWindowFlags(Qt::Tool | Qt::Dialog);
}

WId VideoWidget::request() {
  return winId();
}

void VideoWidget::release() {
}

void VideoWidget::setFullscreen(bool fullscreen) {
  Qt::WindowStates states = windowState();
  if (fullscreen)
    states |= Qt::WindowFullScreen;
  else
    states = states & ~Qt::WindowFullScreen;

  if (states != windowState()) {
    setWindowState(states);
  }
}

void VideoWidget::hideEvent(QHideEvent *) {
  emit visibilityChanged(false);
}

void VideoWidget::showEvent(QShowEvent *) {
  show();
  activateWindow();

  emit visibilityChanged(true);
}
