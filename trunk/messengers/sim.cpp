/*
 * Decoding passwords from SIM
 */

#include "sim.h"

#include <QStringList>
#include <QDebug>
#include <QSettings>

#include "common.h"

sim::sim() {
    root = decoded.createElement("sim");
    decoded.appendChild(root);
    findConfig();
}

QString decodePassword(const QString &hash) {
    QString result;
    QString pswd = hash;
    if (pswd.length() && (pswd[0] == '$')) {
        pswd = pswd.mid(1);
        unsigned short temp = 0x4345;
        foreach(QString str, pswd.split('$')) {
            QString pswdTemp = str;
            temp ^= str.toUShort(0, 16);
            QChar new_temp = QChar(temp);
            result += str.setUnicode(&new_temp, 1);
            temp = pswdTemp.toUShort(0, 16);
        }
    }
    return result;
}

void sim::createXML(QString login, QString pass, QString server) {
    if (!login.isEmpty() && !pass.isEmpty()){
    QDomElement q = decoded.createElement("Account");
    root.appendChild(q);

    QDomElement tag = decoded.createElement("Login");
    q.appendChild(tag);
    QDomText t = decoded.createTextNode(login);
    tag.appendChild(t);

    tag = decoded.createElement("Password");
    q.appendChild(tag);
    t = decoded.createTextNode(pass);
    tag.appendChild(t);
    if (!server.isEmpty()) {
        tag = decoded.createElement("Server");
        q.appendChild(tag);
        t = decoded.createTextNode(server);
        tag.appendChild(t);
    }
}
}

void sim::decoding(QString file) {
    QSettings c(file, QSettings::IniFormat);
    c.beginGroup("jabber/Jabber");
    createXML(c.value("ID").toString(), decodePassword(c.value("Password").toString()), c.value("Server").toString());
    c.endGroup();

    c.beginGroup("icq/AIM");
    createXML(c.value("Screen").toString(), decodePassword(c.value("Password").toString()), QString());
    c.endGroup();

    c.beginGroup("msn/MSN");
    createXML(c.value("EMail").toString(), decodePassword(c.value("Password").toString()), QString());
    c.endGroup();
}

void sim::findConfig() {
    foreach(QString s, dirList(homeDir()+".kde/share/apps/sim"))
        if (QFile::exists(homeDir()+".kde/share/apps/sim/" + s + "/clients.conf"))
            decoding(homeDir()+".kde/share/apps/sim/" + s + "/clients.conf");
}

sim* sim::instance() {
    if (!instance_)
        instance_ = new sim();
    return instance_;
}

sim* sim::instance_ = NULL;
