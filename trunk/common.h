#ifndef COMMON_H
#define COMMON_H

#include <QObject>


QStringList dirList(const QString &directory);
QString homeDir();

/*
class common : public QObject
{
public:
    common();
}; */

#endif // COMMON_H
