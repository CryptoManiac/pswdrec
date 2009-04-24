#include "messengers.h"



#include <QFile>

#include <QDebug>
Messengers::Messengers()
{
}

QString Messengers::psi(const QString &pass, const QString &key) // Decoding passwords from psi
{
        QString result;
        int n1, n2;

        if(key.length() == 0)
                return pass;

        for(n1 = 0, n2 = 0; n1 < pass.length(); n1 += 4) {
                ushort x = 0;
                if(n1 + 4 > pass.length())
                        break;
                x += QString(pass.at(n1)).toInt(NULL,16)*4096;
                x += QString(pass.at(n1+1)).toInt(NULL,16)*256;
                x += QString(pass.at(n1+2)).toInt(NULL,16)*16;
                x += QString(pass.at(n1+3)).toInt(NULL,16);
                QChar c(x ^ key.at(n2++).unicode());
                result += c;
                if(n2 >= key.length())
                        n2 = 0;
        }
        return result;
}

void Messengers::QD()
{

 QDomDocument doc("mydocument");
 QFile file("/home/lastik/.psi/profiles/default/accounts.xml");
 if (!file.open(QIODevice::ReadOnly))
     return;
 if (!doc.setContent(&file)) {
     file.close();
     return;
 }
 file.close();

QDomElement root = doc.documentElement();
 QDomNode node = root.firstChild();
  while (!node.isNull()) {
    if (node.toElement().tagName() == "accounts")
      parseEntry(node.toElement());
    node = node.nextSibling();
  }


}

void Messengers::parseEntry(const QDomElement &element)
{
    QMap<QString,QString> list;
  QDomNode node = element.firstChild();
  while (!node.isNull()) {
   QDomNode nn = node.firstChild();
   QString password, jid;
    while(!nn.isNull()){

        if (nn.toElement().tagName() == "password") {
          QDomNode ppp = nn.firstChild();
          password = ppp.toText().data();
        }

        if (nn.toElement().tagName() == "jid") {
          QDomNode ppp = nn.firstChild();
          jid = ppp.toText().data();
        }

        if (!password.isEmpty() && !jid.isEmpty())
        {
            qDebug() << jid << psi(password, jid);
            password.clear();
            jid.clear();
        }

     nn = nn.nextSibling();
    }
    node = node.nextSibling();
  }
}


