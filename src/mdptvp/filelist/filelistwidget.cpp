#include "filelistwidget.h"
#include "ui_filelistwidget.h"

#include "filelistmodel.h"

#include <QListView>
#include <QModelIndex>
#include <QSettings>
#include <QFileDialog>
#include <QItemSelection>
#include <QItemSelectionModel>

namespace mdptvp {

FileListWidget::FileListWidget(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::FileListWidget),
    model(new FileListModel(this))
{
    ui->setupUi(this);

    ui->listView->setModel(model);
    QObject::connect(ui->listView->selectionModel(),
                     &QItemSelectionModel::currentRowChanged,
                     this,
                     &FileListWidget::current_row_changed);
}

FileListWidget::~FileListWidget()
{
    delete ui;
}

void FileListWidget::on_deleteFilesButton_clicked()
{
    QListView* view = ui->listView;

     view->setUpdatesEnabled(false);
     QModelIndexList selections = view->selectionModel()->selectedIndexes();
     if (!selections.isEmpty()) {
         qSort(selections);
         for(auto it = selections.constEnd(); it != selections.constBegin();) {
             --it;
             model->removeRow(it->row());
         }
     }
     view->setUpdatesEnabled(true);
}

void FileListWidget::on_addFIleButton_clicked()
{
    QSettings settings;
    QString dir = settings.value("lastUsedDirectory").toString();
    QStringList filenames = QFileDialog::getOpenFileNames(this,tr("Escolha o arquivo"), dir);

    if (filenames.isEmpty()) {
        return;
    }

    for (const QString& filename : filenames) {
        model->insertFile(0, filename);
    }
}

void FileListWidget::on_listView_activated(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }

    const QString& filePath = getIndexPath(index);

    emit fileActivated(filePath);
}


void FileListWidget::current_row_changed(const QModelIndex &current, const QModelIndex &previous)
{
    emit fileSelected(getIndexPath(current));
}

const QString FileListWidget::getIndexPath(const QModelIndex &index)
{
    return ui->listView->model()->data(index, Qt::EditRole).toString();
}

} // namespace mdptvp
