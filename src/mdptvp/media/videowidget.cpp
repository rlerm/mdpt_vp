#include "mdptvp/media/videowidget.h"

#include <QtGui/QPalette>
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

#include "mdptvp/util/gui.h"

using ::mdptvp::media::VideoWidget;
namespace util = ::mdptvp::util;

const char* const VideoWidget::MONITOR_KEY = "last_used_monitor";

VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent) {
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

  // Save in which monitor the window is.
  settings_.setValue(MONITOR_KEY,
                     QVariant(QApplication::desktop()->screenNumber(this)));
}

void VideoWidget::showEvent(QShowEvent *) {
  show();
  activateWindow();
  restoreSavedPosition();

  emit visibilityChanged(true);
}

void VideoWidget::restoreSavedPosition() {
  QVariant saved_value = settings_.value(MONITOR_KEY);
  if (saved_value.isValid()) {
    util::moveToScreen(this, saved_value.toInt());
  }
}
