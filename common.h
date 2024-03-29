#ifndef COMMON_H
#define COMMON_H

#include <QObject>


QStringList dirList(const QString &directory);
QString homeDir();
QStringList dirListFiles(const QString &directory, QStringList filter);
QStringList listHomeDirs();

#endif // COMMON_H
