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
    void decoding(const QString &path);
};

#endif // KOPETE_H
