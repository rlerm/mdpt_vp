#ifndef MDPT_FILELIST_FILELISTWIDGET_H_INCLUDED
#define MDPT_FILELIST_FILELISTWIDGET_H_INCLUDED

#include <QGroupBox>

namespace Ui {
class FileListWidget;
}

class QItemSelection;

namespace mdptvp {
namespace filelist {

class FileListModel;

class FileListWidget : public QGroupBox
{
    Q_OBJECT

public:
    explicit FileListWidget(QWidget *parent = 0);
    ~FileListWidget();

    void setModel(FileListModel *file_list);

signals:
    void fileSelected(QString path);

private slots:
    void on_deleteFilesButton_clicked();
    void on_addFIleButton_clicked();
    void itemActivated(const QModelIndex &index);
    // void current_row_changed(const QModelIndex &current,
                             // const QModelIndex &previous);

private:
    Ui::FileListWidget *ui;
    FileListModel *model_;

    const QString getIndexPath(const QModelIndex &index);
};

}  // namespace filelist
}  // namespace mdptvp

#endif // MDPT_FILELIST_FILELISTWIDGET_H_INCLUDED
