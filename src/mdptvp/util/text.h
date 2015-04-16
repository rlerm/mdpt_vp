#ifndef MDPTVP_UTIL_TEXT_H_INCLUDED
#define MDPTVP_UTIL_TEXT_H_INCLUDED

#include <QtCore/QString>

namespace mdptvp {
namespace util {

QString formatTime(int msec);

/**
 * Formats byte quantities in a human-readable and inexact measure.
 */
QString formatBytes(int bytes);

}  // namespace util
}  // namespace mdptvp

#endif  // MDPTVP_UTIL_TEXT_H_INCLUDED
