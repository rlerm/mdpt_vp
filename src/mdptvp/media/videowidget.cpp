#include "mdptvp/media/videowidget.h"

using ::mdptvp::media::VideoWidget;

VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent) {}

WId VideoWidget::request() {
    return winId();
}

void VideoWidget::release() {}

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


