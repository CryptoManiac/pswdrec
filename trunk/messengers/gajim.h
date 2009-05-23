#ifndef GAJIM_H
#define GAJIM_H

#include <QObject>
#include <QtXml/QDomDocument>

class gajim : public QObject
{
public:
    static gajim* instance();
    QDomDocument decoded;

private:
    gajim();
    static gajim* instance_;
    QDomElement root;
    void decoding(QString);
    void createXML(QString, QString, QString);
    void findConfig();
};

#endif // GAJIM_H
