#include "sim.h"

#include <QDebug>
#include <QStringList>

#include "common.h"

sim::sim()
{
    decodePassword("$4337$4352$4322$434f$4339$435f");
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
//    qDebug() << new_pswd;
    QStringList tt = dirList("/home/lastik/.kde/share/apps/sim");

    return new_pswd;
}
