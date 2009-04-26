#include "kftpgrabber.h"

#include <QDebug>

kftpgrabber::kftpgrabber()
{
    qDebug() << decodePassword("cmVwbXZm");
}

QString kftpgrabber::decodePassword(const QString& password)
{
  return QByteArray::fromBase64(password.toAscii().data());
}
