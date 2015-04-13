#ifndef MDPTVP_FILELIST_FILELIST_H_INCLUDED
#define MDPTVP_FILELIST_FILELIST_H_INCLUDED

#include <QHash>
#include <QList>
#include <QObject>

class VlcMedia;
class VlcInstance;

namespace mdptvp {
namespace filelist {

class FileList : public QObject {
  Q_OBJECT

 public:
  FileList(QObject *parent, VlcInstance *instance);

  VlcMedia *at(int index);
  int size();

  void removeItem(int index);
  void addItem(int index, const QString &path);
  void activateItem(int index);

 signals:
  void fileActivated(VlcMedia *activated);

 private:
  static const int OLD_ITEMS_THRESHOLD = 2;

  VlcInstance *vlc_instance_;
  QList<QString> path_list_;
  QHash<QString, VlcMedia*> media_items_;

  void pruneUnused();
};

}  // namespace filelist
}  // namespace mdptvp

#endif  // MDPTVP_FILELIST_FILELIST_H_INCLUDED
