#include "mdptvp/gui/displaylistmodel.h"

#include <QtCore/QObject>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

namespace mdptvp {
namespace gui {

DisplayListModel::DisplayListModel(QObject *parent)
    : QAbstractListModel(parent), desktop_(QApplication::desktop()) {
  screen_count_ = desktop_->screenCount();

  QObject::connect(desktop_, &QDesktopWidget::screenCountChanged,
          this, &DisplayListModel::setScreenCount);
}

DisplayListModel::~DisplayListModel() {}

int DisplayListModel::rowCount(const QModelIndex &parent) const {
    return screen_count_;
}

QVariant DisplayListModel::data(const QModelIndex &index, int role) const {
  if (role != Qt::DisplayRole || index.row() < 0 ||
      index.row() > desktop_->screenCount()) {
    return QVariant();
  }

  return QVariant(QString::number(index.row()));
}

void DisplayListModel::setScreenCount(int new_count) {
  if (new_count > screen_count_) {
    beginInsertRows(QModelIndex(), screen_count_, new_count);
    endInsertRows();
  } else if (new_count < screen_count_) {
    beginRemoveRows(QModelIndex(), new_count, screen_count_);
    endRemoveRows();
  }
  screen_count_ = new_count;
}

}  // namespace gui
}  // namespace mdptvp
