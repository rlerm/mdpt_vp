#ifndef MDPTVP_MEDIA_WIDEOWIDGET_H_INCLUDED
#define MDPTVP_MEDIA_WIDEOWIDGET_H_INCLUDED

#include <QWidget>

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
};

}  // namespace media
}  // namespace mdptvp

#endif  // MDPTVP_MEDIA_WIDEOWIDGET_H_INCLUDED
