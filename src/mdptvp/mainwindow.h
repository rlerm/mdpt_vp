#ifndef MDPTVP_MAINWINDOW_H_INCLUDED
#define MDPTVP_MAINWINDOW_H_INCLUDED

#include <memory>

#include <QMainWindow>

#include "mdptvp/ui_mainwindow.h"
#include "mdptvp/media/playercore.h"

namespace mdptvp {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override = default;

  void closeEvent(QCloseEvent *event);

 private:
  std::unique_ptr<Ui::MainWindow> ui;
  media::PlayerCore *engine_;
};

}  // namespace mdptvp

#endif  // MDPTVP_MAINWINDOW_H_INCLUDED
