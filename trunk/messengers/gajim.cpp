#include "gajim.h"

#include "common.h"

#include <QFile>
#include <QSettings>
#include <QStringList>


gajim::gajim()
{
    root = decoded.createElement("gajim");
    decoded.appendChild(root);
    findConfig();
}

void gajim::decoding(QString path)
{
    QSettings set(path, QSettings::IniFormat);
    foreach(QString str, set.childKeys()) {
        if (str.startsWith("accounts.") && str.contains(".name")) {
            QString host = str; // host = accounts.HOST.XX.name
            host = str.mid(9); // HOST.XX.name
            host = host.left(host.lastIndexOf('.')); // HOST.XX

            QString login = set.value("accounts." + host + ".name").toString();
            QString pass = set.value("accounts." + host + ".password").toString();
            QString server = set.value("accounts." + host + ".hostname").toString();
            createXML(login, pass, server);
        }
    }
}

void gajim::createXML(QString login, QString pass, QString server)
{
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

void gajim::findConfig()
{
    if (QFile::exists(homeDir() + ".gajim/config"))
        decoding(homeDir() + ".gajim/config");
}

gajim* gajim::instance() {
    if (!instance_)
        instance_ = new gajim();
    return instance_;
}

gajim* gajim::instance_ = NULL;
