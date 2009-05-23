#ifndef LICQ_H
#define LICQ_H

#include <QObject>
#include <QtXml/QDomDocument>

class licq : public QObject
{
public:
    static licq* instance();
    QDomDocument decoded;

private:
        licq();
        static licq* instance_;
        QDomElement root;
    void decoding(QString);
    void createXML(QString, QString);
    void findConfig();
};


#endif // LICQ_H
