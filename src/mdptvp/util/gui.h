#ifndef MDPTVP_UTIL_GUI_H_INCLUDED
#define MDPTVP_UTIL_GUI_H_INCLUDED

class QWidget;

namespace mdptvp {
namespace util {


/**
 * Moves the widget to the screen with the specified number.
 *
 * If the screen specified is invalid, it will be moved to the default screen.
 */
void moveToScreen(QWidget* widget, int screen_number);


} // namespace util
} // namespace mdptvp

#endif // MDPTVP_UTIL_GUI_H_INCLUDED
