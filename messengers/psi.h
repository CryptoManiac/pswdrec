#ifndef PSI_H
#define PSI_H
#include <QObject>


class psi : QObject
{
public:
    psi();
    void findConfig();
    QList<QString> decoded;
private:
    QString decodePassword(const QString &pass, const QString &key);
    void decoding(const QString &path);

};

#endif // PSI_H
