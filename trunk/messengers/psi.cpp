/*
Decoding passwords from psi
*/

#include "psi.h"

#include <QFile>
#include <QStringList>
#include <QtXml/QDomDocument>

#include "common.h"

psi::psi()
{
  findConfig();
}

QString psi::decodePassword(const QString &pass, const QString &key)
{
  QString result;
  int n1, n2;

  if(key.length() == 0)
    return pass;

  for(n1 = 0, n2 = 0; n1 < pass.length(); n1 += 4) {
    ushort x = 0;
    if(n1 + 4 > pass.length())
      break;
    x += QString(pass.at(n1)).toInt(NULL, 16) * 4096;
    x += QString(pass.at(n1 + 1)).toInt(NULL, 16) * 256;
    x += QString(pass.at(n1 + 2)).toInt(NULL, 16) * 16;
    x += QString(pass.at(n1 + 3)).toInt(NULL, 16);
    QChar c(x ^ key.at(n2++).unicode());
    result += c;
    if(n2 >= key.length())
      n2 = 0;
  }
  return result;
}

void psi::decoding(const QString &path)
{
        QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

      QDomDocument doc("psi_config");
      doc.setContent(&file);
      QDomElement root = doc.documentElement();
      QDomNode node = root.firstChild();
      while (!node.isNull()) {
        if (node.toElement().tagName() == "accounts") {

          QDomNode yyy = node.toElement().firstChild();
          while (!yyy.isNull()) {
            QDomNode nn = yyy.firstChild();
            QString hash, jid;
            while(!nn.isNull()) {

              if (nn.toElement().tagName() == "password")
                hash = nn.firstChild().toText().data();

              if (nn.toElement().tagName() == "jid")
                jid = nn.firstChild().toText().data();

              if (!hash.isEmpty() && !jid.isEmpty())
              {
                decoded.append("JID: " + jid + " Password: " + decodePassword(hash, jid));
                hash.clear();
                jid.clear();
              }

              nn = nn.nextSibling();
            }
            yyy = yyy.nextSibling();
          }
      }
      node = node.nextSibling();
    }
  }
}


void psi::findConfig()
{

  QStringList list = dirList(homeDir() + ".psi/profiles");
  foreach (QString profile, list)
  {
      QFile file(homeDir() + ".psi/profiles/" + profile + "/config.xml");
        if (file.exists())
      decoding(file.fileName());
        file.setFileName(homeDir() + ".psi/profiles/" + profile + "/accounts.xml");
      if (file.exists())
      decoding(file.fileName());
  }

}
