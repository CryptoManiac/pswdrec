#ifndef UPODT_H
#define UPODT_H

#include <QObject>
#include <QtXml/QDomDocument>

class upodt : public QObject
{
public:
    static upodt* instance();
    bool unRO(QString &);
    QDomDocument analysis(QString &);
private:
    upodt();
    static upodt* instance_;
};

#endif // UPODT_H
