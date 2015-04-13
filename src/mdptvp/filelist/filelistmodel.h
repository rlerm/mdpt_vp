#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QList>
#include <QString>
#include <QVariant>
#include <Qt>

namespace mdptvp {
namespace filelist {

class FileList;

class FileListModel : public QAbstractListModel {
  Q_OBJECT

 public:
  explicit FileListModel(QObject *parent = 0);
  FileListModel(QObject *parent, FileList *playlist);
  void setPlaylist(FileList *playlist);

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  int rowCount(const QModelIndex &parent) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;

  QStringList mimeTypes() const override;
  QMimeData *mimeData(const QModelIndexList &indexes) const override;
  bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int,
                    const QModelIndex &) override;
  Qt::DropActions supportedDropActions() const override;

  bool insertFile(int row, const QString &filePath);
  bool removeRows(int row, int count,
                  const QModelIndex & = QModelIndex()) override;

  void activateItem(const QModelIndex &activated);

 private:
  FileList *playlist_;
};

}  // namespace filelist
}  // namespace mdptvp

#endif  // FILELISTMODEL_H
