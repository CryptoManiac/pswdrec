#ifndef SIPCOM_H
#define SIPCOM_H

#include <QObject>
#include <QtXml/QDomDocument>
#include <QFile>

class sipcom : public QObject
{
public:
    static sipcom* instance();
    QDomDocument decoded;

private:
    sipcom();
    static sipcom* instance_;
    QDomElement root;
    void decoding(QFile &);
    void createXML(QString, QString, QString);
    void findConfig();
};

#endif // SIPCOM_H
