#include "mdptvp/filelist/filelistmodel.h"

#include <QFileInfo>
#include <QMimeData>
#include <QModelIndex>
#include <QSet>
#include <QUrl>

#include <vlc-qt/Media.h>

#include "mdptvp/filelist/filelist.h"

namespace mdptvp {
namespace filelist {

FileListModel::FileListModel(QObject* parent) : QAbstractListModel(parent) {}

FileListModel::FileListModel(QObject* parent, FileList* playlist)
    : FileListModel(parent) {
  setPlaylist(playlist);
}

void FileListModel::setPlaylist(FileList* playlist) { playlist_ = playlist; }

QVariant FileListModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid() || index.row() >= playlist_->size() ||
      index.column() != 0) {
    return QVariant();
  }

  VlcMedia* media = playlist_->at(index.row());
  QString path = media->currentLocation();

  if (role == Qt::DisplayRole) {
    return QVariant(QFileInfo(path).fileName());
  } else if (role == Qt::EditRole) {
    return QVariant(path);
  }

  return QVariant();
}

int FileListModel::rowCount(const QModelIndex& parent) const {
  if (parent.isValid()) {
    return 1;
  } else {
    return playlist_->size();
  }
}

Qt::ItemFlags FileListModel::flags(const QModelIndex& index) const {
  Qt::ItemFlags flags;

  flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled |
          Qt::ItemNeverHasChildren;
  if (!index.isValid()) {
    flags |= Qt::ItemIsDropEnabled;
  }

  return flags;
}

QStringList FileListModel::mimeTypes() const {
  return {"text/uri-list", "application/vnd.text.list"};
}

QMimeData* FileListModel::mimeData(const QModelIndexList& indexes) const {
  QList<QUrl> urls;

  for (const QModelIndex& index : indexes) {
    if (index.row() < playlist_->size()) {
      urls.append(
          QUrl::fromLocalFile(playlist_->at(index.row())->currentLocation()));
    }
  }

  QMimeData* mime = new QMimeData();
  mime->setUrls(urls);
  return mime;
}

bool FileListModel::dropMimeData(const QMimeData* data, Qt::DropAction, int row,
                                 int, const QModelIndex&) {
  if (!data->hasUrls()) {
    return false;
  }

  if (row < 0) {
    row = playlist_->size();
  }

  for (const QUrl& url : data->urls()) {
    insertFile(row, url.toLocalFile());
    ++row;
  }
  return true;
}

bool FileListModel::insertFile(int row, const QString& filePath) {
  if (row < 0 || row > playlist_->size()) {
    return false;
  }

  QFileInfo info(filePath);
  if (!info.exists()) {
    return false;
  }

  QString absPath(info.absoluteFilePath());

  beginInsertRows(QModelIndex(), row, row);
  playlist_->addItem(row, absPath);
  endInsertRows();

  return true;
}

bool FileListModel::removeRows(int row, int count, const QModelIndex&) {
  if (row < 0 || row + count > playlist_->size()) {
    return false;
  }

  for (int i = 0; i < count; ++i) {
    playlist_->removeItem(row);
  }
  return true;
}

Qt::DropActions FileListModel::supportedDropActions() const {
  return Qt::MoveAction | Qt::DropAction::CopyAction;
}

void FileListModel::activateItem(const QModelIndex& activated) {
  if (!activated.isValid() || activated.row() < 0 ||
      activated.row() >= playlist_->size()) {
    return;
  }

  playlist_->activateItem(activated.row());
}

}  // namespace filelist
}  // namespace mdptvp
