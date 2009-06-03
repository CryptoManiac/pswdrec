#ifndef KMAIL_H
#define KMAIL_H

#include <QObject>
#include <QtXml/QDomDocument>

class kmail : public QObject
{
public:
    static kmail* instance();
    QDomDocument decoded;

private:
    kmail();
    static kmail* instance_;
    QDomElement root;
    void decoding(QString);
    void createXML(QString, QString, QString);
    void findConfig();
    QString decodePassword(const QString &);
};

#endif // KMAIL_H
