#ifndef MDPTVP_MAINWINDOW_H_INCLUDED
#define MDPTVP_MAINWINDOW_H_INCLUDED

#include <QMainWindow>

// Forward-declarations.
class VlcMedia;
namespace Ui {
class MainWindow;
} // namespace Ui
namespace mdptvp {
namespace media {
class PlayerCore;
} // namespace media
} // namespace mdptvp


namespace mdptvp {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void closeEvent(QCloseEvent *event);

 private:
  Ui::MainWindow *ui;
  media::PlayerCore *engine_;

  void connectSignals();

 private slots:
  void setPlayState(bool should_play);
  void setOutputVisibility(bool visible);
  void setOutputFullscreen(bool fullscreen);
};
}  // namespace mdptvp

#endif  // MDPTVP_MAINWINDOW_H_INCLUDED
