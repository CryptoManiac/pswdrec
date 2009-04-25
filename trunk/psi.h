#ifndef PSI_H
#define PSI_H
#include <QObject>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomText>

class psi : QObject
{
public:
    psi();
        void findConfig();

    QList<QString> decoded;
private:
    QString decodePassword(const QString &pass, const QString &key);

};

#endif // PSI_H
