#include "common.h"

#include <QStringList>
#include <QDir>

#include <QDebug>

QStringList dirList(const QString &directory)
{
    QDir dir(directory);
    dir.setFilter(QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    return dir.entryList().count() ? dir.entryList() : QStringList();
 }

QString homeDir()
{
      return QDir::homePath() + '/';
}
