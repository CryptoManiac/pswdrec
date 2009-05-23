#ifndef KOPETE_H
#define KOPETE_H

#include <QObject>
#include <QtXml/QDomDocument>

class kopete : public QObject
{
public:
    static kopete* instance();
    QDomDocument decoded;
private:
    kopete();
    QString decodePassword(QString);
    void decoding(QString);
    void createXML(QString, QString, QString);
    QDomElement root;
    void findConfig();
            static kopete* instance_;
};

#endif // KOPETE_H
