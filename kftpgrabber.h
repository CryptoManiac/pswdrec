#ifndef KFTPGRABBER_H
#define KFTPGRABBER_H

#include <QObject>

class kftpgrabber : public QObject
{
public:
    kftpgrabber();
    private:
    QString decodePassword(const QString& password);
};

#endif // KFTPGRABBER_H
