#ifndef ALICQ_H
#define ALICQ_H

#include <QObject>
#include <QtXml/QDomDocument>
#include <QFile>

class alicq : public QObject {
public:
    static alicq* instance();
    QDomDocument decoded;

private:
    alicq();
    static alicq* instance_;
    QDomElement root;
    void decoding(QFile &);
    void createXML(QString, QString);
    void findConfig();
};

#endif // ALICQ_H
