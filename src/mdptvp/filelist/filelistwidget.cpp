#include "filelistwidget.h"
#include "ui_filelistwidget.h"

#include "filelistmodel.h"

#include <QtCore/QItemSelection>
#include <QtCore/QItemSelectionModel>
#include <QtCore/QModelIndex>
#include <QtCore/QSettings>
#include <QtWidgets/QAction>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QListView>
#include <QtWidgets/QListView>


using mdptvp::filelist::FileListModel;
using mdptvp::filelist::FileListWidget;

const char* FileListWidget::ADD_ICON_PATH = ":/icons/add";
const char* FileListWidget::REMOVE_ICON_PATH = ":/icons/delete";

FileListWidget::FileListWidget(QWidget *parent)
    : QGroupBox(parent),
      ui(new Ui::FileListWidget),
      add_file_action_(
          new QAction(QIcon(ADD_ICON_PATH), tr("&Adicionar arquivo"), this)),
      remove_file_action_(
          new QAction(QIcon(REMOVE_ICON_PATH), tr("Remover arquivo"), this)) {
  ui->setupUi(this);

  QObject::connect(ui->list_view_, &QListView::activated, this,
                   &FileListWidget::itemActivated);

  connect(add_file_action_, &QAction::triggered,
          [this](bool) { on_addFIleButton_clicked(); });
  connect(remove_file_action_, &QAction::triggered,
          [this](bool) { on_deleteFilesButton_clicked(); });
}

FileListWidget::~FileListWidget() {
  delete ui;
}

void FileListWidget::setModel(FileListModel *model) {
  ui->list_view_->setModel(model);
  model_ = model;
}

void FileListWidget::on_deleteFilesButton_clicked() {
  QListView *view = ui->list_view_;

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

void FileListWidget::itemActivated(const QModelIndex &index) {
  if (!index.isValid()) {
    return;
  }

  model_->activateItem(index);
}

const QString FileListWidget::getIndexPath(const QModelIndex &index) {
  return model_->data(index, Qt::EditRole).toString();
}

QAction *FileListWidget::getAddFileAction() const {
  return add_file_action_;
}
QAction *FileListWidget::getRemoveFileAction() const {
    return remove_file_action_;
}
