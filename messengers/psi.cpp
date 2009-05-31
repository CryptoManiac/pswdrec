/*
 * Decoding passwords from psi
 */

#include "psi.h"

#include <QFile>
#include <QStringList>
#include <QtXml/QDomDocument>

#include "common.h"

psi::psi() {
    root = decoded.createElement("psi");
    decoded.appendChild(root);
    findConfig();
}

QString psi::decodePassword(const QString &pass, const QString &key) {
    QString result;
    int n1, n2;
    if(key.length() == 0)
        return pass;
    for(n1 = 0, n2 = 0; n1 < pass.length(); n1 += 4) {
        ushort x = 0;
        if(n1 + 4 > pass.length())
            break;
        x += QString(pass.at(n1)).toInt(NULL, 16) * 4096;
        x += QString(pass.at(n1 + 1)).toInt(NULL, 16) * 256;
        x += QString(pass.at(n1 + 2)).toInt(NULL, 16) * 16;
        x += QString(pass.at(n1 + 3)).toInt(NULL, 16);
        QChar c(x ^ key.at(n2++).unicode());
        result += c;
        if(n2 >= key.length())
            n2 = 0;
    }
    return result;
}

void psi::createXML(QString login, QString pass, QString server) {
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


void psi::decoding(QFile &path) {
    QDomDocument doc;
    doc.setContent(&path);
    QDomElement root = doc.documentElement();
    QDomNode node = root.firstChild();
    while (!node.isNull()) {
        if (node.toElement().tagName() == "accounts") {
            QDomNode yyy = node.toElement().firstChild();
            while (!yyy.isNull()) {
                QDomNode nn = yyy.firstChild();
                QString hash, jid, host;
                while(!nn.isNull()) {
                    if (nn.toElement().tagName() == "password")
                        hash = nn.firstChild().toText().data();
                    if (nn.toElement().tagName() == "jid")
                        jid = nn.firstChild().toText().data();
                    if (nn.toElement().tagName() == "host")
                        host = nn.firstChild().toText().data();
                    nn = nn.nextSibling();
                }
                createXML(jid, decodePassword(hash, jid), host);
                yyy = yyy.nextSibling();
            }
        }
        node = node.nextSibling();
    }
}


void psi::findConfig() {
    foreach(QString profile, dirList(homeDir() + ".psi/profiles")) {
        QFile file(homeDir() + ".psi/profiles/" + profile + "/config.xml");
        if (file.open(QIODevice::ReadOnly)){
            decoding(file);
            file.close();
        }
        file.setFileName(homeDir() + ".psi/profiles/" + profile + "/accounts.xml");
        if (file.open(QIODevice::ReadOnly))
            decoding(file);
    }
}

psi* psi::instance() {
    if (!instance_)
        instance_ = new psi();
    return instance_;
}

psi* psi::instance_ = NULL;
