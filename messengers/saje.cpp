#include "saje.h"

#include "common.h"

#include <QDebug>

saje::saje()
{
    root = decoded.createElement("saje");
    decoded.appendChild(root);
    findConfig();
}

void swap(char *b1, char *b2) {
 char b = *b1;
 *b1 = *b2;
 *b2 = b;
}

void arc4_init(arc4_ctx *ctx, char *key, int keylen) {
        int i;
        for(i = 0; i < 256; i++)
                ctx->lookup[i] = i;

        ctx->x = 0;
        for(i = 0; i < 256; i++) {
        ctx->x = (key[i % keylen] + ctx->lookup[i] + ctx->x) & 0xFF;
        swap(&ctx->lookup[ctx->x], &ctx->lookup[i]);
        }
        ctx->x = 0;
        ctx->y = 0;
}

void arc4_crypt(arc4_ctx *ctx, char *dataIn, char *dataOut, int datalen) {
        for(int i = 0; i < datalen; i++) {
                ctx->x = (ctx->x + 1) & 0xFF;
                ctx->y = (ctx->lookup[ctx->x] + ctx->y) & 0xFF;
                swap(&ctx->lookup[ctx->x], &ctx->lookup[ctx->y]);
                dataOut[i] = (dataIn[i] ^ ctx->lookup[(ctx->lookup[ctx->x] + ctx->lookup[ctx->y]) & 0xFF]);
        }
}

QByteArray crypt(const QByteArray b, const QString &key) {
        QString k;
        k = key;

        QByteArray bk = k.toUtf8();

        char *out = (char *)malloc(b.length());
        arc4_ctx ctx;
        arc4_init(&ctx, bk.data(), bk.length());
        arc4_crypt(&ctx, (char *)b.data(), out, b.length());

        QByteArray ret = QByteArray(out, b.length());
        free(out);
        return ret;
}


QString saje::decodePassword(const QByteArray &hash, const QString &key) {

        QString k = key;

        QByteArray bk = k.toUtf8();

        char *out = (char *)malloc(hash.length());
        arc4_ctx ctx;
        arc4_init(&ctx, bk.data(), bk.length());
        arc4_crypt(&ctx, (char *)hash.data(), out, hash.length());

        QByteArray ret = QByteArray(out, hash.length());
        free(out);
        return ret;
}

void saje::createXML(QString login, QString pass, QString server, QString protocol) {
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

void saje::decoding(QFile &file) {
        QDomDocument tempDoc;
        tempDoc.setContent(&file);
        QDomNode nRoot = tempDoc.documentElement();
        for (int i = 0;i < nRoot.childNodes().count();i++) {
                if (nRoot.childNodes().at(i).toElement().tagName() == "account-data") {
                    QString login = nRoot.childNodes().at(i).toElement().attribute("username");
                    QString server = nRoot.childNodes().at(i).toElement().attribute("host");
                    QString proto = nRoot.childNodes().at(i).toElement().attribute("protocol-name");
                    QString key = login + server;
                    QString tmp = nRoot.childNodes().at(i).toElement().attribute("password");
                    QString pass = decodePassword(QByteArray::fromBase64(tmp.toUtf8()), key);

                    createXML(login, pass, server, proto);
                }
            }

}

void saje::findConfig() {
    QFile file(homeDir()+".config/Saje/accounts.xml");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        decoding(file);
}

saje* saje::instance() {
    if (!instance_)
        instance_ = new saje();
    return instance_;
}

saje* saje::instance_ = NULL;
