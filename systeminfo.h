#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QObject>

class SystemInfo : public QObject
{
public:
	static SystemInfo* instance();
	const QString& os() const { return os_str_; }
        QString localHostName_();
        QString kernelVersion();
private:
	SystemInfo();

	static SystemInfo* instance_;
	QString os_str_;
};

#endif
