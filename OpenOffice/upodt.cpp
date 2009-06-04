#include "upodt.h"

#include <QTextStream>
#include <QFile>

#include <QDebug>
upodt::upodt() {
}

QDomElement unROel()
{
    QDomDocument oth;
    QDomElement newN = oth.createElement("config:config-item");
    newN.setAttribute("config:name", "LoadReadonly");
    newN.setAttribute("config:type", "boolean");
    oth.appendChild(newN);
    QDomText t = oth.createTextNode("false");
    newN.appendChild(t);
    qDebug() << oth.toString();
    return newN;
}

bool upodt::unRO(QString &fileN) {
    QFile f(fileN);
    if (f.exists()) {
        QDomDocument p;
        p.setContent(&f);
        QDomElement root = p.documentElement().firstChild().toElement();

        for (int i = 0;i < root.childNodes().count();i++) {
            if (root.childNodes().at(i).toElement().attribute("config:name") == "ooo:configuration-settings") {

                QDomElement pook = root.childNodes().at(i).toElement();
                for (int j = 0;j < pook.childNodes().count();j++) {

                    QDomElement kop = pook.childNodes().at(j).toElement();
                    if (kop.attribute("config:name") == "LoadReadonly") {

                        pook.replaceChild(unROel(), kop);
                        break;break;
                    }
                }
            }
        }
        f.close();
        f.open(QFile::WriteOnly);
        QTextStream str(&f);
        p.save(str, 0);
        f.close();
        return true;
    }
    return false;
}

QDomDocument upodt::analysis(QString &fileN) {

}

upodt* upodt::instance() {
    if (!instance_)
        instance_ = new upodt();
    return instance_;
}

upodt* upodt::instance_ = NULL;
