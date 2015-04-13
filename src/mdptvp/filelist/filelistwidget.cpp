#include "filelistwidget.h"
#include "ui_filelistwidget.h"

#include "filelistmodel.h"

#include <QListView>
#include <QModelIndex>
#include <QSettings>
#include <QFileDialog>
#include <QItemSelection>
#include <QItemSelectionModel>

using mdptvp::filelist::FileListModel;
using mdptvp::filelist::FileListWidget;

FileListWidget::FileListWidget(QWidget *parent)
    : QGroupBox(parent),
      ui(new Ui::FileListWidget) {
  ui->setupUi(this);

  QObject::connect(ui->listView->selectionModel(),
                   &QItemSelectionModel::currentRowChanged, this,
                   &FileListWidget::current_row_changed);
}

FileListWidget::~FileListWidget() { delete ui; }

void FileListWidget::setModel(FileListModel *model) {
    ui->listView->setModel(model);
    model_ = model;
}

void FileListWidget::on_deleteFilesButton_clicked() {
  QListView *view = ui->listView;

  view->setUpdatesEnabled(false);
  QModelIndexList selections = view->selectionModel()->selectedIndexes();
  if (!selections.isEmpty()) {
    qSort(selections);
    for (auto it = selections.constEnd(); it != selections.constBegin();) {
      --it;
      model_->removeRow(it->row());
    }
  }
  view->setUpdatesEnabled(true);
}

void FileListWidget::on_addFIleButton_clicked() {
  QSettings settings;
  QString dir = settings.value("lastUsedDirectory").toString();
  QStringList filenames =
      QFileDialog::getOpenFileNames(this, tr("Escolha o arquivo"), dir);

  if (filenames.isEmpty()) {
    return;
  }

  for (const QString &filename : filenames) {
    model_->insertFile(0, filename);
  }
}

void FileListWidget::on_listView_activated(const QModelIndex &index) {
  if (!index.isValid()) {
    return;
  }

  model_->activateItem(index);
}

void FileListWidget::current_row_changed(const QModelIndex &current,
                                         const QModelIndex &previous) {
  emit fileSelected(getIndexPath(current));
}

const QString FileListWidget::getIndexPath(const QModelIndex &index) {
  return model_->data(index, Qt::EditRole).toString();
}

