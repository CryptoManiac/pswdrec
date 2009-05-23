#include "licq.h"

#include <QSettings>
#include <QFile>
#include <QStringList>

#include <common.h>

licq::licq() {
    root = decoded.createElement("licq");
    decoded.appendChild(root);
    findConfig();
}


void licq::findConfig() {
    QStringList owners;
    owners.append("owner.*");
    foreach(QString s, dirListFiles(homeDir()+".licq", owners))
            if (QFile::exists(homeDir()+".licq/" + s))
                decoding(homeDir()+".licq/" + s);
}

void licq::decoding(QString path) {
    QSettings c(path, QSettings::IniFormat);

    if (c.childGroups().count() != 0) {
        c.beginGroup("user");
    }
    QString login = c.value("UIN").toString();
    QString pass = c.value("Password").toString();
    createXML(login, pass);

}

void licq::createXML(QString login, QString pass) {
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
    }
}

licq* licq::instance() {
    if (!instance_)
        instance_ = new licq();
    return instance_;
}

licq* licq::instance_ = NULL;
