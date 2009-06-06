#ifndef UPODT_H
#define UPODT_H

#include <QObject>
#include <QtXml/QDomDocument>
#include <QFile>

class upodt : public QObject
{
public:
    static upodt* instance();
    bool unRO(QString &, bool, QString &);
    QDomDocument analysis(QString &);
private:
    upodt();
    static upodt* instance_;
};

#endif // UPODT_H
