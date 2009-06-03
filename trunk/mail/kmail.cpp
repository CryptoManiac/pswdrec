#include "kmail.h"

#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QStringList>

#include <QDebug>

#include "common.h"

kmail::kmail() {
    root = decoded.createElement("kmail");
    decoded.appendChild(root);
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


void kmail::createXML(QString login, QString pass, QString server) {
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
    qDebug() << decoded.toString();
}

void kmail::decoding(QString path)
{
   QSettings set(path, QSettings::IniFormat);
       foreach(QString str, set.childGroups()) {
        if (str.startsWith("Account ")) {
            set.beginGroup(str);
            QString login = set.value("login").toString();
            QString pass = decodePassword(set.value("pass").toString());
            QString server = set.value("host").toString();
            createXML(login, pass, server);
            set.endGroup();
        }
    }
}

void kmail::findConfig()
{
    QFile file(homeDir() + ".kde4/share/config/kmailrc");
    if (file.exists()) {
        decoding(file.fileName());
        file.close();
    }
    file.setFileName(homeDir() + ".kde/share/config/kmailrc");
    if (file.exists())
        decoding(file.fileName());
}

kmail* kmail::instance() {
    if (!instance_)
        instance_ = new kmail();
    return instance_;
}

kmail* kmail::instance_ = NULL;
