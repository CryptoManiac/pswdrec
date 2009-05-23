#include "alicq.h"

#include <common.h>

alicq::alicq() {
    root = decoded.createElement("alicq");
    decoded.appendChild(root);
    findConfig();
}


void alicq::findConfig() {
    QFile file(homeDir()+".alicq/alicqrc");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        decoding(file);
}

void alicq::decoding(QFile &file) {
    QString login, pass;
    while (!file.atEnd()) {
        QString str = file.readLine();
        if (str.startsWith("icq uin "))
            login = str.right(str.length() - str.indexOf(' ', 5));
        if (str.startsWith("icq password "))
            pass = str.right(str.length() - str.indexOf(' ', 5));
    }
    createXML(login, pass);
}

void alicq::createXML(QString login, QString pass) {
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

alicq* alicq::instance() {
    if (!instance_)
        instance_ = new alicq();
    return instance_;
}

alicq* alicq::instance_ = NULL;
