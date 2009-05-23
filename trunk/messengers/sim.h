#ifndef SIM_H
#define SIM_H

#include <QObject>
#include <QFile>
#include <QtXml/QDomDocument>

class sim : public QObject
{
public:
    static sim* instance();
    QDomDocument decoded;

private:
        sim();
        static sim* instance_;
        QDomElement root;
    void decoding(QString);
    void createXML(QString, QString, QString);
    void findConfig();
};

#endif // SIM_H
