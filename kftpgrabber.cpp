#include "kftpgrabber.h"

#include <QDebug>

kftpgrabber::kftpgrabber()
{
    //qDebug() << decodePassword("");
}

QString kftpgrabber::decodePassword(const QString& password)
{
  return QByteArray::fromBase64(password.toAscii().data());
}
