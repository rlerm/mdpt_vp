#ifndef MDPTVP_GUI_ABOUTDIALOG_H
#define MDPTVP_GUI_ABOUTDIALOG_H

#include <memory>

#include <QDialog>

namespace mdptvp {
namespace gui {

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog {
  Q_OBJECT

 public:
  explicit AboutDialog(QWidget *parent = 0);
  ~AboutDialog();

 private:
  std::unique_ptr<Ui::AboutDialog> ui;
};

}  // namespace gui
}  // namespace mdptvp
#endif  // MDPTVP_GUI_ABOUTDIALOG_H
