#ifndef MDPTVP_MAINWINDOW_H_INCLUDED
#define MDPTVP_MAINWINDOW_H_INCLUDED

#include <QMainWindow>

class VlcMedia;

namespace Ui {
class MainWindow;
}

namespace mdptvp {

namespace media {
class PlayerCore;
}  // namespace media

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
