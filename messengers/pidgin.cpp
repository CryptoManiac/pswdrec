#include "pidgin.h"

#include <QDebug>
#include <QFile>

#include "common.h"


pidgin::pidgin() {
    root = decoded.createElement("pidgin");
    decoded.appendChild(root);
    findConfig();
}

void pidgin::createXML(QString login, QString pass, QString proto) {
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

        tag = decoded.createElement("Protocol");
        q.appendChild(tag);
        proto = proto.right(proto.length() - proto.indexOf('-') - 1);
        t = decoded.createTextNode(proto);
        tag.appendChild(t);

    }
}

void pidgin::decoding(QFile &file) {
    QDomDocument qDoc;
    qDoc.setContent(&file);
    QDomNode nRoot = qDoc.documentElement().firstChild();
    while (!nRoot.isNull()) {
        QString protocol, login, pass;
        for (int i = 0;i < nRoot.childNodes().count();i++) {

            if (nRoot.childNodes().at(i).toElement().tagName() == "protocol")
                protocol = nRoot.childNodes().at(i).toElement().text();

            if (nRoot.childNodes().at(i).toElement().tagName() == "name")
                login = nRoot.childNodes().at(i).toElement().text();

            if (nRoot.childNodes().at(i).toElement().tagName() == "password")
                pass = nRoot.childNodes().at(i).toElement().text();
        }
        createXML(login, pass, protocol);

        nRoot = nRoot.nextSiblingElement();
    }

}

void pidgin::findConfig() {
    QFile file(homeDir() + ".purple/accounts.xml");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        decoding(file);
}


pidgin* pidgin::instance() {
    if (!instance_)
        instance_ = new pidgin();
    return instance_;
}

pidgin* pidgin::instance_ = NULL;
