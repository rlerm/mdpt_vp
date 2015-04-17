#ifndef MDPT_FILELIST_FILELISTWIDGET_H_INCLUDED
#define MDPT_FILELIST_FILELISTWIDGET_H_INCLUDED

#include <QtCore/QDir>
#include <QtCore/QSettings>
#include <QtWidgets/QGroupBox>

namespace Ui {
class FileListWidget;
}

class QAction;
class QItemSelection;

namespace mdptvp {
namespace filelist {

class FileListModel;

class FileListWidget : public QGroupBox {
  Q_OBJECT

 public:
  explicit FileListWidget(QWidget *parent = 0);
  ~FileListWidget();

  void setModel(FileListModel *file_list);

  QAction *getAddFileAction() const;
  QAction *getRemoveFileAction() const;

 private slots:
  void on_deleteFilesButton_clicked();
  void on_addFIleButton_clicked();
  void itemActivated(const QModelIndex &index);

 private:
  static const char *ADD_ICON_PATH;
  static const char *REMOVE_ICON_PATH;
  static const char *LAST_DIRECTORY_KEY;

  QDir getDefaultOpenDirectory();
  const QString getIndexPath(const QModelIndex &index);

  QSettings settings_;
  Ui::FileListWidget *ui;
  FileListModel *model_;
  QAction *add_file_action_;
  QAction *remove_file_action_;
};

}  // namespace filelist
}  // namespace mdptvp

#endif  // MDPT_FILELIST_FILELISTWIDGET_H_INCLUDED
