#ifndef KMAIL_H
#define KMAIL_H

#include <QObject>

class kmail : public QObject
{
public:
    kmail();
    void findConfig();
    QList<QString> decoded;
private:
    QString decodePassword(const QString &pass);
    void decoding(const QString &path);
};

#endif // KMAIL_H
