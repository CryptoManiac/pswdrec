#ifndef SIM_H
#define SIM_H

#include <QObject>
#include <QFile>
#include <QtXml/QDomDocument>

class sim : public QObject
{
public:
    static sim* instance();
    void findConfig();
    QDomDocument decoded;
    void decoding(QFile&);
    void createXML(QString &, QString &);
private:
        sim();
        static sim* instance_;
        QDomElement root;
};

#endif // SIM_H
