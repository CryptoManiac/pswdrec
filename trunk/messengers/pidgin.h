#ifndef PIDGIN_H
#define PIDGIN_H

#include <QObject>
#include <QtXml/QDomDocument>
#include <QFile>

class pidgin : public QObject
{
public:
    static pidgin* instance();
    QDomDocument decoded;

private:
        pidgin();
        static pidgin* instance_;
        QDomElement root;
        void decoding(QFile &);
        void createXML(QString, QString, QString);
        void findConfig();
};

#endif // PIDGIN_H
