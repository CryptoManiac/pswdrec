#ifndef MDC_H
#define MDC_H

#include <QObject>
#include <QtXml/QDomDocument>

class mdc : public QObject
{
public:
    mdc();
   static mdc* instance();
    void findConfig();
    void decoding(const QString &);
        QDomDocument decoded;
        void createXML(QString &, QString &, QString &);
private:
  static mdc* instance_;
          QDomElement root;
};

#endif // MDC_H
