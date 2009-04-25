#ifndef MESSENGERS_H
#define MESSENGERS_H

#include <QObject>

class Messengers : public QObject
{
public:
    Messengers();
    QString kopete( const QString &str );
};

#endif // MESSENGERS_H
