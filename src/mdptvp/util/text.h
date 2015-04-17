#ifndef MDPTVP_UTIL_TEXT_H_INCLUDED
#define MDPTVP_UTIL_TEXT_H_INCLUDED

#include <QtCore/QString>
#include <QtCore/QTextCodec>

namespace mdptvp {
namespace util {

/**
 * Formats a time amount (in milliseconds) into a human-readable format.
 */
QString formatTime(int msec);

/**
 * Formats byte quantities in a human-readable and inexact measure.
 */
QString formatBytes(int bytes);

/**
 * Reads an text file into a QString.
 */
QString readFile(const QString &path,
                 QTextCodec *codec = QTextCodec::codecForName("utf-8"));

}  // namespace util
}  // namespace mdptvp

#endif  // MDPTVP_UTIL_TEXT_H_INCLUDED
