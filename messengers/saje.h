#ifndef SAJE_H
#define SAJE_H

#include <QObject>
#include <QtXml/QDomDocument>
#include <QFile>
typedef struct {
        char lookup[256];
        int x, y;
} arc4_ctx;

class saje : public QObject
{
public:
    static saje* instance();
    QDomDocument decoded;

private:
    saje();
    static saje* instance_;
    QDomElement root;
    void decoding(QFile &);
    void createXML(QString, QString, QString, QString);
    void findConfig();
    QString decodePassword(const QByteArray &, const QString &);
};

#endif // SAJE_H
