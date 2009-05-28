#include "ayttm.h"

#include <QFile>
#include <QDebug>

#include "common.h"


ayttm::ayttm() {
    root = decoded.createElement("ayttm");
    decoded.appendChild(root);
    findConfig();
}

//enum {NONE, ROT13, XOR13, MAX_ENC};
QString decode_password(QString pass_in, int enc_type) {
    QString pwd;
  /*  for(int i = 0;pass_in.length();i++) {
        pwd.at(i) = pass_in.at(i);
        if(enc_type == 1) {
            if(pwd.at(i) >= 'a' && pwd.at(i) <='z') {
                pwd.at(i) = (pwd.at(i) - 'a' + 13) % 26 + 'a';
            } else if(pwd.at(i) >= 'A' && pwd.at(i) <='Z') {
                pwd.at(i) = (pwd.at(i) - 'A' + 13) % 26 + 'A';
            } else if(pwd.at(i) >= '0' && pwd.at(i) <='9') {
                pwd.at(i) = (pwd.at(i) - '0' + 5) % 10 + '0';
            }
        } else if(enc_type == 2) {
            if(pwd.at(i) >= 'a' && pwd.at(i) <='x') {
                pwd.at(i) = ((pwd.at(i) - 'a') ^ 2) + 'a';
            } else if(pwd.at(i) >= 'x' && pwd.at(i) <='z') {
                pwd.at(i) = ((pwd.at(i) - 'a') ^ 1) + 'a';
            } else if(pwd.at(i) >= 'A' && pwd.at(i) <='X') {
                pwd.at(i) = ((pwd.at(i) - 'A') ^ 2) + 'A';
            } else if(pwd.at(i) >= 'X' && pwd.at(i) <='Z') {
                pwd.at(i) = ((pwd.at(i) - 'A') ^ 1) + 'A';
            } else if(pwd.at(i) >= '0' && pwd.at(i) <='7') {
                pwd.at(i) = ((pwd.at(i) - '0') ^ 2) + '0';
            } else if(pwd.at(i) >= '8' && pwd.at(i) <='9') {
                pwd.at(i) = ((pwd.at(i) - '0') ^ 1) + '0';
            }
        }
    }

    pwd.at(i)='\0';
*/
    return pwd;
}

QString ayttm::decodePassword(QString hash) {

}

void ayttm::createXML(QString login, QString pass, QString server) {

}

QString pars(QString inStr) {
    inStr = inStr.mid(1);
    inStr = inStr.right(inStr.length() - inStr.indexOf('\"') - 1);
    inStr = inStr.left(inStr.lastIndexOf('\"'));
    return inStr;
}

void ayttm::decoding(QString file) {
    QFile acFile(file);

    if (acFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString login, pass, server, protocol;
        int enc;
        while (!acFile.atEnd()) {
            QString str = acFile.readLine();
            if (str.startsWith('#')) continue;
            if (str.startsWith("<ACCOUNT ")) {
                protocol = str.right(str.length() - str.indexOf(' ') + 1);
                protocol = protocol.left(protocol.indexOf('>'));
            }

            if (str.mid(1).startsWith("SCREEN_NAME")) {
                login = pars(str);
            }

            if (str.mid(1).startsWith("CONNECT_SERVER")) {
                server = pars(str);
            }
            if (str.mid(1).startsWith("enc_type")) {
                enc = pars(str).toInt();
            }
            if (str.mid(1).startsWith("password_encoded")) {
                pass = decode_password(pars(str), enc);
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
