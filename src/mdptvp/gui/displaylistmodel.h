#ifndef MDPTVP_GUI_DISPLAYLISTMODEL_H_INCLUDED
#define MDPTVP_GUI_DISPLAYLISTMODEL_H_INCLUDED

#include <QtCore/QAbstractListModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtWidgets/QDesktopWidget>

namespace mdptvp {
namespace gui {

class DisplayListModel : public QAbstractListModel {
  Q_OBJECT
 public:
  DisplayListModel(QObject *parent = nullptr);
  ~DisplayListModel();

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

 private slots:
  void setScreenCount(int new_count);

 private:
  QDesktopWidget *desktop_;
  int screen_count_;
};

}  // namespace gui
}  // namespace mdptvp

#endif  // MDPTVP_GUI_DISPLAYLISTMODEL_H_INCLUDED
