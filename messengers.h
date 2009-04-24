#ifndef MESSENGERS_H
#define MESSENGERS_H

#include <QObject>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomText>

class Messengers : public QObject
{
public:
    Messengers();

    QString psi(const QString &pass, const QString &key);
    void QD();
    void parseEntry(const QDomElement &element);
};

#endif // MESSENGERS_H
