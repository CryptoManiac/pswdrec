#include "kopete.h"

#include <QFile>
#include <QStringList>
#include <QDebug>

#include <QSettings>
#include <QtXml/QDomDocument>


#include "common.h"


kopete::kopete() {
    root = decoded.createElement("kopete");
    decoded.appendChild(root);
    findConfig();
}

QString kopete::decodePassword(QString pass) {
    QString result;
    const QChar *unicode = pass.unicode();
    for (int i = 0; i < pass.length(); ++i)
        result += (unicode[i].unicode() < 0x21) ? unicode[i] : QChar(0x1001F - unicode[i].unicode());
    return result;
}

void kopete::decoding(QString path) {
    QSettings set(path, QSettings::IniFormat);
    foreach(QString str, set.childGroups()) {
        if (str.startsWith("Account_")) {
            set.beginGroup(str);
            QString login = set.value("AccountID").toString();
            QString pass = decodePassword(set.value("Password").toString());
            QString server = set.value("Server").toString();
            createXML(login, pass, server);
            set.endGroup();
        }
    }
}

void kopete::createXML(QString login, QString pass, QString server) {
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

void kopete::findConfig() {

    if (QFile::exists(homeDir() + ".kde4/share/config/kopeterc"))
        decoding(homeDir() + ".kde4/share/config/kopeterc");
    if (QFile::exists(homeDir() + ".kde/share/config/kopeterc"))
        decoding(homeDir() + ".kde/share/config/kopeterc");
}

kopete* kopete::instance() {
    if (!instance_)
        instance_ = new kopete();
    return instance_;
}

kopete* kopete::instance_ = NULL;
