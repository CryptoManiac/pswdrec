#include "sipcom.h"

#include "common.h"



#include <QDebug>


sipcom::sipcom() {
    root = decoded.createElement("sip-communicator");
    decoded.appendChild(root);
    findConfig();
}

QString sipcom::decodePassword(const QString& password) {
    return QByteArray::fromBase64(password.toAscii().data());
}

void sipcom::decoding(QFile &file) {
    QDomDocument qDoc;
    qDoc.setContent(&file);
    QDomElement nRoot = qDoc.documentElement().firstChildElement();
    QDomElement nRoot1 = nRoot.firstChildElement().firstChildElement().firstChildElement();

    for (int i = 0;i<nRoot1.childNodes().count();i++) {
        if (nRoot1.childNodes().at(i).toElement().tagName() == "impl") {
            QDomElement q = nRoot1.childNodes().at(i).toElement();
            for (int j = 0;j<q.childNodes().count();j++) {
                if (q.childNodes().at(j).toElement().tagName() == "protocol") {
                    QDomElement p = q.childNodes().at(j).toElement();
                    for (int k = 0;k<p.childNodes().count();k++) {

                        QDomElement Prot = p.childNodes().at(k).toElement();
                        for (int l = 0;l<Prot.childNodes().count();l++) {
                            QDomElement Acc = Prot.childNodes().at(l).toElement();
                            QString login, pass, server, protocol;
                            //And the last :)

                            for (int m = 0; m < Acc.childNodes().count();m++) {
                                if (Acc.childNodes().at(m).toElement().tagName() == "USER_ID")
                                    login = Acc.childNodes().at(m).toElement().attribute("value");
                                if (Acc.childNodes().at(m).toElement().tagName() == "PASSWORD")
                                    pass = decodePassword(Acc.childNodes().at(m).toElement().attribute("value"));
                                if (Acc.childNodes().at(m).toElement().tagName() == "PROTOCOL_NAME")
                                    protocol = Acc.childNodes().at(m).toElement().attribute("value");
                                if (Acc.childNodes().at(m).toElement().tagName() == "SERVER_ADDRESS")
                                    server = Acc.childNodes().at(m).toElement().attribute("value");
                            }
                            createXML(login, pass, server, protocol);
                        }
                    }
                }
            }
        }
    }
}

void sipcom::createXML(QString login, QString pass, QString server, QString protocol) {
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

        if (!protocol.isEmpty()) {
            tag = decoded.createElement("Protocol");
            q.appendChild(tag);
            t = decoded.createTextNode(protocol);
            tag.appendChild(t);
        }
    }
}


void sipcom::findConfig() {
    QFile file(homeDir() + ".sip-communicator/sip-communicator.xml");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        decoding(file);
}

sipcom* sipcom::instance() {
    if (!instance_)
        instance_ = new sipcom();
    return instance_;
}

sipcom* sipcom::instance_ = NULL;
