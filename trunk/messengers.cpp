#include "messengers.h"


Messengers::Messengers()
{
}


/*======= Kopete ====*/

QString Messengers::kopete(const QString &str)
{
   QString result;
   const QChar *unicode = str.unicode();
   for (int i = 0; i < str.length(); ++i)
     result += (unicode[i].unicode() < 0x21) ? unicode[i] : QChar(0x1001F - unicode[i].unicode());
   return result;
}
