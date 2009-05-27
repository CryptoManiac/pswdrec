#ifndef AYTTM_H
#define AYTTM_H

#include <QObject>

#include <QtXml/QDomDocument>

class ayttm : public QObject
{
public:
    static ayttm* instance();
    QDomDocument decoded;

private:
    ayttm();
    static ayttm* instance_;
    QDomElement root;
    void decoding(QString);
    void createXML(QString, QString, QString);
    void findConfig();
    QString decodePassword(QString);
};

#endif // AYTTM_H
