#ifndef FILELISTWIDGET_H
#define FILELISTWIDGET_H

#include <QGroupBox>

namespace Ui {
class FileListWidget;
}

class QItemSelection;

namespace mdptvp {

class FileListModel;

class FileListWidget : public QGroupBox
{
    Q_OBJECT

public:
    explicit FileListWidget(QWidget *parent = 0);
    ~FileListWidget();

signals:
    void fileActivated(QString path);
    void fileSelected(QString path);

private slots:
    void on_deleteFilesButton_clicked();
    void on_addFIleButton_clicked();
    void on_listView_activated(const QModelIndex &index);
    void current_row_changed(const QModelIndex &current,
                             const QModelIndex &previous);

private:
    Ui::FileListWidget *ui;
    FileListModel *model;

    const QString getIndexPath(const QModelIndex &index);
};

}

#endif // FILELISTWIDGET_H
