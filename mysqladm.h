#ifndef MYSQLADM_H
#define MYSQLADM_H

#include <QObject>
#include <QFile>
#include <QtXml/QDomDocument>

class mysqladm : public QObject
{
public:
    static mysqladm* instance();
    QDomDocument decoded;

private:
    mysqladm();
    static mysqladm* instance_;
    QDomElement root;
    void decoding(QFile &);
    void createXML(QString, QString, QString, QString);
    void findConfig();
    char* obscure(char*);
    char* hex_decode(const char*, int*);
};

#endif // MYSQLADM_H
