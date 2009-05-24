#include "sipcom.h"

#include "common.h"



#include <QDebug>


sipcom::sipcom() {
    root = decoded.createElement("sip-communicator");
    decoded.appendChild(root);
    findConfig();
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
                              //And the last :)

                                for (int m = 0; m < Acc.childNodes().count();m++)
                            {
                                    qDebug() << Acc.childNodes().at(m).toElement().text();

                                }

                         }
                    }
                }
            }
        }
    }

//createXML(login, pass, protocol);
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
