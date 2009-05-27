#include "ayttm.h"

#include <QFile>
#include <QDebug>

#include "common.h"


ayttm::ayttm() {
    root = decoded.createElement("sim");
    decoded.appendChild(root);
    findConfig();
}

enum {NONE, ROT13, XOR13, MAX_ENC};
const char *decode_password(const char *pass_in, int enc_type)
{
        static char pwd[1024];
        int i;
        for(i=0; pass_in[i] && i<1023; i++) {
                pwd[i] = pass_in[i];
                if(enc_type == ROT13) {
                        if(pwd[i] >= 'a' && pwd[i] <='z') {
                                pwd[i] = (pwd[i]-'a' + 13)%26 + 'a';
                        } else if(pwd[i] >= 'A' && pwd[i] <='Z') {
                                pwd[i] = (pwd[i]-'A' + 13)%26 + 'A';
                        } else if(pwd[i] >= '0' && pwd[i] <='9') {
                                pwd[i] = (pwd[i]-'0' + 5)%10 + '0';
                        }
                } else if(enc_type == XOR13) {
                        if(pwd[i] >= 'a' && pwd[i] <='x') {
                                pwd[i] = ((pwd[i]-'a')^2) + 'a';
                        } else if(pwd[i] >= 'x' && pwd[i] <='z') {
                                pwd[i] = ((pwd[i]-'a')^1) + 'a';
                        } else if(pwd[i] >= 'A' && pwd[i] <='X') {
                                pwd[i] = ((pwd[i]-'A')^2) + 'A';
                        } else if(pwd[i] >= 'X' && pwd[i] <='Z') {
                                pwd[i] = ((pwd[i]-'A')^1) + 'A';
                        } else if(pwd[i] >= '0' && pwd[i] <='7') {
                                pwd[i] = ((pwd[i]-'0')^2) + '0';
                        } else if(pwd[i] >= '8' && pwd[i] <='9') {
                                pwd[i] = ((pwd[i]-'0')^1) + '0';
                        }
                }
        }

        pwd[i]='\0';

        return pwd;
}

QString ayttm::decodePassword(QString hash) {

}

void ayttm::createXML(QString login, QString pass, QString server) {

}

void ayttm::decoding(QString file) {

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
