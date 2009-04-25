#ifndef KOPETE_H
#define KOPETE_H

#include <QObject>

class kopete : public QObject
{
public:
    kopete();
    void findConfig();
    QList<QString> decoded;
private:
    QString decodePassword(const QString &pass);
};

#endif // KOPETE_H
