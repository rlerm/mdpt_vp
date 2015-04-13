#include "mdptvp/gui/util.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

namespace gui = ::mdptvp::gui;

void gui::moveToScreen(QWidget* widget, int screen_number) {
  QDesktopWidget* desktop = QApplication::desktop();
  if (screen_number >= desktop->screenCount()) {
    screen_number = -1;
  }

  widget->move(desktop->availableGeometry(screen_number).topLeft());
}
