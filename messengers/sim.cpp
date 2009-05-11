/*
 * Decoding passwords from SIM
 */

#include "sim.h"

#include <QStringList>
#include <QFile>
#include <QTextStream>

#include "common.h"

sim::sim()
{
    findConfig();
}

QString sim::decodePassword(const QString &hash)
{
    QString result;
    QString pswd = hash;
    if (pswd.length() && (pswd[0] == '$'))
    {
        pswd = pswd.mid(1);
        unsigned short temp = 0x4345;
        foreach(QString str, pswd.split('$'))
        {
            QString pswdTemp = str;
            temp ^= str.toUShort(0, 16);
            QChar new_temp = QChar(temp);
            result += str.setUnicode(&new_temp, 1);
            temp = pswdTemp.toUShort(0, 16);
        }
    }
    return result;
}

void sim::findConfig()
{
    QStringList list = dirList(homeDir()+".kde/share/apps/sim");
    foreach(QString s, list)
    {
        QFile file(homeDir()+".kde/share/apps/sim/" + s + "/clients.conf");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {

            QString login;
            QString pass;
            QTextStream in(&file);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                line.truncate(line.length() - 1);
                if (line.startsWith("ID="))
                {
                    login = line.right(line.length() - 4);
                    decoded.append("Login: " + login + " Pass: " + pass);
                    pass.clear();
                    login.clear();
                }

                if (line.startsWith("Password="))
                    pass = decodePassword(line.right(line.length() - 10));

            }
        }
    }
}
