#include "mdc.h"

#include <QFile>
#include <QStringList>
#include <QDebug>

#include "common.h"

mdc::mdc()
{
    findConfig();
}

void mdc::findConfig()
{
    QStringList list = dirList(homeDir() + ".MDC");
    foreach (QString profile, list)
    {
        QFile file(homeDir() + ".MDC/" + profile + "/ss.scs");
        if (file.exists())
        {
            decoding(file.fileName());
        }
    }

}


void mdc::decoding(const QString &path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly))
    {
            QByteArray text = QByteArray::fromBase64(file.readAll());
            decoded.setContent(text);
            qDebug() << decoded.toString();
    }
}
