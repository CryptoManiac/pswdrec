#ifndef MDC_H
#define MDC_H

#include <QObject>
#include <QtXml/QDomDocument>

class mdc : public QObject
{
public:
    mdc();
    void findConfig();
    void decoding(const QString &);
        QDomDocument decoded;
};

#endif // MDC_H
