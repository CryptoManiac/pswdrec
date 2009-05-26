#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QObject>
#include <QtXml/QDomDocument>

class SystemInfo : public QObject
{
public:
	static SystemInfo* instance();
        QDomDocument collect();
private:
	SystemInfo();
	static SystemInfo* instance_;
        QString getOS();
        QString localHostName();
        QString kernelVersion();
        QString currentUser();
};

#endif
