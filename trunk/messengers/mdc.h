#ifndef MDC_H
#define MDC_H

#include <QObject>
#include <QtXml/QDomDocument>
#include <QFile>

class mdc : public QObject
{
public:
    mdc();
    static mdc* instance();
    QDomDocument decoded;

private:
    static mdc* instance_;
    QDomElement root;
    void findConfig();
    void decoding(QFile &);
    void createXML(QString &, QString &, QString &);
};

#endif // MDC_H
