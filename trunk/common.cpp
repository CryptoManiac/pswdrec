#include "common.h"

#include <QStringList>
#include <QDir>

#include <QDebug>

/*common::common()
{
}*/
QStringList dirList(const QString &directory)
{
    QDir dir(directory);
    dir.setFilter(QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    //QStringList result = dir.entryList();
    return dir.entryList().count() ? dir.entryList() : QStringList();
 }

QString homeDir()
{
      return QDir::homePath() + '/';
}
