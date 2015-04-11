#include "mdptvp/filelist/filelistmodel.h"

#include <QModelIndex>
#include <QMimeData>
#include <QUrl>

namespace mdptvp {

FileListModel::FileListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QVariant FileListModel::data(const QModelIndex & index, int role) const {
    if (!index.isValid()
            || index.row() >= fileList.size()
            || index.column() != 0) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        return QVariant(fileList[index.row()].baseName());
    } else if (role == Qt::EditRole) {
        return QVariant(fileList[index.row()].absoluteFilePath());
    }

    return QVariant();
}

int FileListModel::rowCount(const QModelIndex &parent) const {
    return fileList.size();

    if (parent.isValid()) {
        return 0;
    } else {
        return fileList.size();
    }
}

Qt::ItemFlags FileListModel::flags(const QModelIndex & index) const {
    Qt::ItemFlags flags;

    flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled
            | Qt::ItemNeverHasChildren;
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
        if (index.row() < fileList.size()) {
            urls.append(QUrl::fromLocalFile(
                            fileList[index.row()].absoluteFilePath()));
        }
    }

    QMimeData* mime = new QMimeData();
    mime->setUrls(urls);
    return mime;
}

bool FileListModel::dropMimeData(const QMimeData * data, Qt::DropAction, int row, int , const QModelIndex&) {
    if (!data->hasUrls()) {
        return false;
    }

    if (row < 0) {
        row = fileList.size();
    }

    for (const QUrl& url : data->urls()) {
        insertFile(row, url.toLocalFile());
        ++row;
    }
    return true;
}

bool FileListModel::insertFile(int row, const QString& filePath) {
    if (row < 0 || row > fileList.size()) {
        return false;
    }

    QFileInfo info(filePath);
    if (!info.exists()) {
        return false;
    }

    beginInsertRows(QModelIndex(), row, row);
    fileList.insert(row, info);
    endInsertRows();

    return true;
}

bool FileListModel::removeRows(int row, int count, const QModelIndex&) {
    if (row < 0 || row + count > fileList.size()) {
        return false;
    }

    for (int i = 0; i < count; ++i) {
        fileList.removeAt(row);
    }
    return true;
}

Qt::DropActions FileListModel::supportedDropActions() const
{
    return Qt::MoveAction | Qt::DropAction::CopyAction;
}

} // namespace mdptvp
