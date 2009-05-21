/*
 * Decoding passwords from SIM
 */

#include "sim.h"

#include <QStringList>
#include <QTextStream>
#include <QDebug>

#include "common.h"

sim::sim():QObject() {
    root = decoded.createElement("sim");
    decoded.appendChild(root);
    findConfig();
    qDebug()<< decoded.toString();
}

QString decodePassword(const QString &hash) {
    QString result;
    QString pswd = hash;
    if (pswd.length() && (pswd[0] == '$')) {
        pswd = pswd.mid(1);
        unsigned short temp = 0x4345;
        foreach(QString str, pswd.split('$')) {
            QString pswdTemp = str;
            temp ^= str.toUShort(0, 16);
            QChar new_temp = QChar(temp);
            result += str.setUnicode(&new_temp, 1);
            temp = pswdTemp.toUShort(0, 16);
        }
    }
    return result;
}

void sim::createXML(QString &login, QString &pass) {
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

void sim::decoding(QFile &file) {
    QString login, pass;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        line.truncate(line.length() - 1);
        if (line.startsWith("ID=") || line.startsWith("Screen=")) {
            login = line.right(line.length() - 4);
            createXML(login, pass);
            pass.clear();
            login.clear();
        }

        if (line.startsWith("Password="))
            pass = decodePassword(line.right(line.length() - 10));

    }
}

void sim::findConfig() {
    QStringList list = dirList(homeDir()+".kde/share/apps/sim");
    foreach(QString s, list) {
        QFile file(homeDir()+".kde/share/apps/sim/" + s + "/clients.conf");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            decoding(file);
    }
}

sim* sim::instance() {
    if (!instance_)
        instance_ = new sim();
    return instance_;
}

sim* sim::instance_ = NULL;
