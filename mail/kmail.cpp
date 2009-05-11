#include "kmail.h"

#include <QFile>
#include <QTextStream>

#include "common.h"

kmail::kmail() {
    findConfig();
}

QString kmail::decodePassword(const QString &pass)
{
    QString result;
    const QChar *unicode = pass.unicode();
    for (int i = 0; i < pass.length(); ++i)
        result += (unicode[i].unicode() < 0x21) ? unicode[i] : QChar(0x1001F - unicode[i].unicode());
    return result;
}

void kmail::decoding(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QString login;
    QString pass;
    QString host;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.startsWith("login="))
            login = line.right(line.length() - 6);
        if (line.startsWith("host="))
            host = line.right(line.length() - 5);
        if (line.startsWith("pass="))
        {
            pass = decodePassword(line.right(line.length() - 5));
            decoded.append("Login: " + login + " Host: " + host + " Pass: " + pass);
            pass.clear();
            login.clear();
            host.clear();
        }
    }
}

void kmail::findConfig()
{
    QFile file(homeDir() + ".kde4/share/config/kmailrc");
    if (file.exists())
        decoding(file.fileName());
    file.setFileName(homeDir() + ".kde/share/config/kmailrc");
    if (file.exists())
        decoding(file.fileName());
}
