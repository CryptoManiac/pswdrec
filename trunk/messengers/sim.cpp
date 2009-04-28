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
    QString new_pswd;
    QString pswd = hash;
    if (pswd.length() && (pswd[0] == '$')) {
        pswd = pswd.mid(1);
        unsigned short temp = 0x4345;
        QStringList qq = pswd.split('$');
        foreach(QString s, qq){
            QString p = s;
            temp ^= s.toUShort(0,16);
            QChar pppp = QChar(temp);
            new_pswd += s.setUnicode(&pppp,1);
            temp = p.toUShort(0,16);
        }
    }
    return new_pswd;
}

void sim::findConfig()
{
    QStringList list = dirList(homeDir()+".kde/share/apps/sim");
    foreach (QString s, list)
    {
     QFile file(homeDir()+".kde/share/apps/sim/" + s + "/clients.conf");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){

        QString login;
        QString pass;
        QTextStream in(&file);
     while (!in.atEnd()) {
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
