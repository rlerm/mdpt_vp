#ifndef MDPTVP_MAINWINDOW_H_INCLUDED
#define MDPTVP_MAINWINDOW_H_INCLUDED

#include <memory>

#include <QMainWindow>

// Forward-declarations.
class VlcMedia;
namespace Ui {
class MainWindow;
}  // namespace Ui
namespace mdptvp {
namespace media {
class PlayerCore;
}  // namespace media
}  // namespace mdptvp


namespace mdptvp {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow() override = default;

  void closeEvent(QCloseEvent *event);

 private:
  std::unique_ptr<Ui::MainWindow> ui;
  media::PlayerCore *engine_;
};

}  // namespace mdptvp

#endif  // MDPTVP_MAINWINDOW_H_INCLUDED
