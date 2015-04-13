#ifndef MDPTVP_GUI_UTIL_H_INCLUDED
#define MDPTVP_GUI_UTIL_H_INCLUDED

class QWidget;

namespace mdptvp {
namespace gui {


/**
 * Moves the widget to the screen with the specified number.
 *
 * If the screen specified is invalid, it will be moved to the default screen.
 */
void moveToScreen(QWidget* widget, int screen_number);


} // namespace gui
} // namespace mdptvp

#endif // MDPTVP_GUI_UTIL_H_INCLUDED
