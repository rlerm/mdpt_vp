#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QtCore/QDebug>

#include "mdptvp/util/text.h"

namespace mdptvp {
namespace gui {

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AboutDialog) {
  ui->setupUi(this);

  QString text = util::readFile(":/text/about");
  qDebug() << text;
  ui->about_label_->setText(text);
}

AboutDialog::~AboutDialog() {
}

}  // namespace gui
}  // namespace mdptvp
