#ifndef GGADGETS_H
#define GGADGETS_H

#include <QObject>
#include <QtXml/QDomDocument>
#include <QFile>

class ggadgets : public QObject
{
public:
    static ggadgets* instance();
    QDomDocument decoded;

private:
    ggadgets();
    static ggadgets* instance_;
    QDomElement root;
    void decoding(QFile &);
    void createXML(QString, QString, QString);
    void findConfig();
};

#endif // GGADGETS_H
