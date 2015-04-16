#include "mdptvp/util/text.h"

#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QStringBuilder>
#include <QtCore/QTime>
#include <QtCore/QVector>

namespace util = ::mdptvp::util;

QString util::formatTime(int msec) {
  int sec = msec / 1000;
  int min = sec / 60;
  sec %= 60;
  int hour = min / 60;
  min %= 60;

  QString lower = QString("%1:%2")
      .arg(min, 2, 10, QChar('0'))
      .arg(sec, 2, 10, QChar('0'));
  if (hour > 0) {
    return QString("%1").arg(hour, 1) + lower;
  } else {
    return lower;
  }
}

const QVector<QString> SI_MULTIPLIERS = {"", "K", "M", "G", "T"};

QString util::formatBytes(int bytes) {
  float readable = bytes;

  // This indicates that the multiplier to be shown is 1024*multiplier.
  int multiplier = 0;

  while (readable >= 1024 && multiplier < SI_MULTIPLIERS.size()) {
    readable /= 1024;
    ++multiplier;
  }
  return QString::number(readable, 'f', 2) %
      SI_MULTIPLIERS.at(multiplier) % "B";
}
