#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <Qt>
#include <QAbstractListModel>
#include <QList>
#include <QFileInfo>
#include <QVariant>

namespace mdptvp {

class FileListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit FileListModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QStringList mimeTypes () const override;
    QMimeData *mimeData(const QModelIndexList & indexes) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int, const QModelIndex &) override;
    Qt::DropActions supportedDropActions() const override;

    bool insertFile(int row, const QString& filePath);
    bool removeRows(int row, int count,
                    const QModelIndex & = QModelIndex()) override;

private:
    QList<QFileInfo> fileList;

signals:
public slots:
};

}

#endif // FILELISTMODEL_H
