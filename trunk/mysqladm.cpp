#include "mysqladm.h"

#include "common.h"
#include <QDebug>

mysqladm::mysqladm() {
    root = decoded.createElement("mysqladmin");
    decoded.appendChild(root);
    findConfig();
}

char* mysqladm::obscure(char* str) {
    if (!str) {
        return 0;
    }
    else {
        long len = (long)strlen((char*)str);
        char *result = (char*)malloc(len + 1);
        char *res_pos = result;
        char *res_end = result + len;
        for (; res_pos != res_end; res_pos++, str++)
            *res_pos = ~(*str);
        *res_pos = 0;
        return result;
    }
}

char* mysqladm::hex_decode(const char *hex_str, int *ret_str_len) {
    int i;
    int hex_str_len, result_len;
    char *result;
    
    hex_str_len = (int) strlen(hex_str);
    
    result_len = hex_str_len / 2;
    result = (char*)malloc(result_len + 1);
    if (ret_str_len) *ret_str_len = result_len;
    
    for (i= 0; i < result_len; i++) {
        unsigned int num;
        sscanf(hex_str + i * 2, "%2x", &num);
        result[i] = num;
    }
    result[i] = 0;
    return (char*)result;
}

void mysqladm::findConfig() {
    QFile file(homeDir() + ".mysqlgui/mysqlx_user_connections.xml");
    if (file.open(QIODevice::ReadOnly))
        decoding(file);
}

void mysqladm::createXML(QString login, QString pass, QString host, QString port) {
    
    if (!pass.isEmpty()) {
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
        
        tag = decoded.createElement("Hostname");
        q.appendChild(tag);
        t = decoded.createTextNode(host);
        tag.appendChild(t);
        
        tag = decoded.createElement("Port");
        q.appendChild(tag);
        t = decoded.createTextNode(port);
        tag.appendChild(t);
    }
}

void mysqladm::decoding(QFile &path) {
    QDomDocument tempDoc;
    tempDoc.setContent(&path);
    
    QDomNode nRoot = tempDoc.documentElement().firstChild();
    
    while (!nRoot.isNull()) {
        if (nRoot.toElement().tagName() == "user_connection") {
            QString login, pass, host, port;
            QString passST;
            for (int i = 0;i < nRoot.childNodes().count();i++) {
                QString chName = nRoot.childNodes().at(i).toElement().tagName();
                QString chPar = nRoot.childNodes().at(i).toElement().text();
                if (chName == "username")
                    login = chPar;
                if (chName == "hostname")
                    host = chPar;
                if (chName == "port")
                    port = chPar;
                if (chName == "password_storage_type")
                    passST = chPar;
                if (chName == "password") {
                    if (passST == "1" || passST == "2")
                        pass = chPar;
                    if (passST == "3") {
                        char *dec = hex_decode(chPar.toLatin1(), NULL); // QByteArray::fromHex() doesn't work :(
                        pass = QString(obscure(dec));
                    }
                }
                
            }
            createXML(login, pass, host, port);
        }
        nRoot = nRoot.nextSiblingElement();
    }
}



mysqladm* mysqladm::instance() {
    if (!instance_)
        instance_ = new mysqladm();
    return instance_;
}

mysqladm* mysqladm::instance_ = NULL;
