#include "mdptvp/util/gui.h"

#include <Qt>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QWidget>

namespace mdptvp {
namespace util {

void moveToScreen(QWidget* widget, int screen_number) {
  QDesktopWidget* desktop = QApplication::desktop();
  if (screen_number >= desktop->screenCount()) {
    screen_number = -1;
  }

  // Moving between desktops doesn't work for fullscreen windows, so we use this
  // ugly hack. We un-fullscreen the widget, move it, and then restore the
  // previous window state. For windows that are not fullscreen, this has no
  // effect since the previous state is restored.
  Qt::WindowStates old_state = widget->windowState();
  widget->setWindowState(widget->windowState() & ~Qt::WindowFullScreen);

  widget->move(desktop->availableGeometry(screen_number).topLeft());

  widget->setWindowState(old_state);
}

} // namespace util
} // namespace mdptvp
