#include "ayttm.h"

#include <QFile>
#include <QDebug>

#include "common.h"


ayttm::ayttm() {
    root = decoded.createElement("ayttm");
    decoded.appendChild(root);
    findConfig();
}

const char* ayttm::decode_password(const char *pass_in, int enc_type)
{
        static char pwd[1024];
        int i;
        for(i = 0; pass_in[i] && i < 1023; i++) {
                pwd[i] = pass_in[i];
                if(enc_type == 1) {
                        if(pwd[i] >= 'a' && pwd[i] <='z') {
                                pwd[i] = (pwd[i] - 'a' + 13)%26 + 'a';
                        } else if(pwd[i] >= 'A' && pwd[i] <='Z') {
                                pwd[i] = (pwd[i] - 'A' + 13)%26 + 'A';
                        } else if(pwd[i] >= '0' && pwd[i] <='9') {
                                pwd[i] = (pwd[i] - '0' + 5)%10 + '0';
                        }
                } else if(enc_type == 2) {
                        if(pwd[i] >= 'a' && pwd[i] <='x') {
                                pwd[i] = ((pwd[i] - 'a') ^ 2) + 'a';
                        } else if(pwd[i] >= 'x' && pwd[i] <='z') {
                                pwd[i] = ((pwd[i] - 'a') ^ 1) + 'a';
                        } else if(pwd[i] >= 'A' && pwd[i] <='X') {
                                pwd[i] = ((pwd[i] - 'A') ^ 2) + 'A';
                        } else if(pwd[i] >= 'X' && pwd[i] <='Z') {
                                pwd[i] = ((pwd[i] - 'A') ^ 1) + 'A';
                        } else if(pwd[i] >= '0' && pwd[i] <='7') {
                                pwd[i] = ((pwd[i] - '0') ^ 2) + '0';
                        } else if(pwd[i] >= '8' && pwd[i] <='9') {
                                pwd[i] = ((pwd[i] - '0') ^ 1) + '0';
                        }
                }
        }

        pwd[i]='\0';
qDebug() << pwd;
        return pwd;
}

void ayttm::createXML(QString login, QString pass, QString server, QString proto) {
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
        tag = decoded.createElement("Protocol");
        q.appendChild(tag);
        t = decoded.createTextNode(proto);
        tag.appendChild(t);
    }
}

QString ayttm::pars(QString inStr) {
    inStr = inStr.mid(1);
    inStr = inStr.right(inStr.length() - inStr.indexOf('\"') - 1);
    inStr = inStr.left(inStr.lastIndexOf('\"'));
    return inStr;
}

void ayttm::decoding(QString file) {
    QFile acFile(file);

    if (acFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString login, pass, server, protocol;
        int enc = 0;
        while (!acFile.atEnd()) {
            QString str = acFile.readLine();
            if (str.startsWith('#')) continue;
            if (str.startsWith("<ACCOUNT ")) {
                protocol = str.right(str.length() - str.indexOf(' ') - 1);
                protocol = protocol.left(protocol.indexOf('>'));
            }
            if (str.mid(1).startsWith("SCREEN_NAME"))
                login = pars(str);
            if (str.mid(1).startsWith("CONNECT_SERVER") || str.mid(1).startsWith("irc_host"))
                server = pars(str);
            if (str.mid(1).startsWith("enc_type"))
                enc = pars(str).toInt();
            if (str.mid(1).startsWith("password_encoded"))
                pass = decode_password(pars(str).toLatin1(), enc);
            if (str.mid(1).startsWith("PASSWORD"))
                pass = pars(str);
            if (str.startsWith("</ACCOUNT>")) {
                createXML(login, pass, server, protocol);
                login.clear();
                pass.clear();
                server.clear();
                protocol.clear();
            }
        }
    }
}

void ayttm::findConfig() {
    if (QFile::exists(homeDir()+".ayttm/accounts"))
        decoding(homeDir()+".ayttm/accounts");
}

ayttm* ayttm::instance() {
    if (!instance_)
        instance_ = new ayttm();
    return instance_;
}

ayttm* ayttm::instance_ = NULL;
