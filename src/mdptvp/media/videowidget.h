#ifndef MDPTVP_MEDIA_WIDEOWIDGET_H_INCLUDED
#define MDPTVP_MEDIA_WIDEOWIDGET_H_INCLUDED

#include <QtCore/QSettings>
#include <QtWidgets/QWidget>
#include <QCloseEvent>
#include <QCloseEvent>
#include <QHideEvent>
#include <QShowEvent>
#include <QSettings>

#include <vlc-qt/VideoDelegate.h>

namespace mdptvp {
namespace media {

class VideoWidget : public QWidget, public VlcVideoDelegate {
  Q_OBJECT
 public:
  explicit VideoWidget(QWidget *parent = nullptr);

  WId request() override;
  void release() override;

 public slots:
  void setFullscreen(bool fullscreen);

 signals:
  void visibilityChanged(bool visible);

 private:
  void hideEvent(QHideEvent *event) override;
  void showEvent(QShowEvent *event) override;

  /**
   * If a previously used output is defined, moves the window there.
   * If not, nothing happens.
   */
  void restoreSavedPosition();

  QSettings settings_;

  static const char* const MONITOR_KEY;
};

}  // namespace media
}  // namespace mdptvp

#endif  // MDPTVP_MEDIA_WIDEOWIDGET_H_INCLUDED
