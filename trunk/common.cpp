#include "common.h"

#include <QStringList>
#include <QDir>
#include <QFile>
#include <QDebug>

QStringList dirList(const QString &directory)
{
    QDir dir(directory);
    dir.setFilter(QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    return dir.entryList().count() ? dir.entryList() : QStringList();
 }

QStringList dirListFiles(const QString &directory, QStringList filter)
{
    QDir dir(directory);
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setNameFilters(filter);
    return dir.entryList().count() ? dir.entryList() : QStringList();
}

QString homeDir()
{
      return QDir::homePath() + '/';
}

QStringList listHomeDirs()
{
    QStringList result;
    QFile passwd("/etc/passwd");
    if (passwd.open(QIODevice::ReadOnly | QIODevice::Text)){
         while (!passwd.atEnd()) {
         QString line = passwd.readLine();
         QStringList list = line.split(':');
         result.append(list.at(5));
     }
    }
    return result;
}
