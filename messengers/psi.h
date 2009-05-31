#ifndef PSI_H
#define PSI_H
#include <QObject>

#include <QFile>
#include <QtXml/QDomDocument>

class psi : QObject
{
public:
    static psi* instance();
    QDomDocument decoded;
private:
    psi();
    static psi* instance_;
    QDomElement root;
    QString decodePassword(const QString &pass, const QString &key);
    void decoding(QFile &);
    void findConfig();
    void createXML(QString, QString, QString);
};

#endif // PSI_H
