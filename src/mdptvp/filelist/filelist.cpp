#include "mdptvp/filelist/filelist.h"

#include <QDebug>
#include <QSet>

#include <vlc-qt/Media.h>

using mdptvp::filelist::FileList;

FileList::FileList(QObject *parent, VlcInstance *instance)
    : QObject(parent), vlc_instance_(instance) {}

VlcMedia *FileList::at(int index) {
  QString path = path_list_.at(index);
  return media_items_.value(path);
}

int FileList::size() { return path_list_.size(); }

void FileList::removeItem(int index) { path_list_.removeAt(index); }

void FileList::addItem(int index, const QString &path) {
  if (!media_items_.contains(path)) {
    VlcMedia *media = new VlcMedia(path, true, vlc_instance_);
    media_items_.insert(path, media);
  }

  path_list_.insert(index, path);

  // If needed, remove unused media items.
  if (media_items_.size() > OLD_ITEMS_THRESHOLD * path_list_.size()) {
    pruneUnused();
  }
}

void FileList::pruneUnused() {
  QSet<QString> toRemove = media_items_.keys().toSet();
  toRemove.subtract(path_list_.toSet());

  for (const QString &key : toRemove) {
    VlcMedia *removed = media_items_.take(key);
    delete removed;
  }
}

void FileList::activateItem(int index) {
  QString path = path_list_.at(index);
  qDebug() << "File activated: " << path;
  emit fileActivated(media_items_.value(path));
}
