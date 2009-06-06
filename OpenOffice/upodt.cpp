#include "upodt.h"

#include <QTextStream>
#include <QFile>
#include <QDebug>

#include "libltzip/include/qunzip.hh"
#include "libltzip/include/qzip.hh"

using namespace lt;

upodt::upodt() {
}

QDomElement unROel() {
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

bool upodt::unRO(QString &fileN, bool check /* For checking RO-files*/ ,
        QString &inFile /* For checking RO-files*/ ) {
    QFile f(fileN);

    if (f.exists() || check) {
        QDomDocument p;
        if (check) {
            p.setContent(inFile);
        } else {
            p.setContent(&f);
        }
        QDomElement root = p.documentElement().firstChild().toElement();

        for (int i = 0;i < root.childNodes().count();i++) {
            if (root.childNodes().at(i).toElement().attribute("config:name") == "ooo:configuration-settings") {

                QDomElement pook = root.childNodes().at(i).toElement();
                for (int j = 0;j < pook.childNodes().count();j++) {

                    QDomElement kop = pook.childNodes().at(j).toElement();
                    if (kop.attribute("config:name") == "LoadReadonly") {
                        if (!check) {
                            pook.replaceChild(unROel(), kop);
                            f.close();
                            f.open(QFile::WriteOnly);
                            QTextStream str(&f);
                            p.save(str, 0);
                            f.close();
                            return true;
                        } else {
                            if (kop.text() == "true")
                                return true;
                            else
                                return false;
                        }
                        break;break;
                    }
                }
            }
        }

    }
    return false;
}
/*
 * void repack(QString zipFileName)
 * {
 * QFile zipFile(zipFileName);
 * zipFile.open(IO_ReadOnly);
 * CPPUNIT_ASSERT(zipFile.isOpen());
 *
 * QUnZip u;
 * CPPUNIT_ASSERT(u.open(&zipFile));
 *
 * QBuffer newZip;
 * newZip.open(IO_ReadWrite);
 *
 * QZip z;
 * CPPUNIT_ASSERT(z.open(&newZip));
 *
 * int filescount = 0;
 * if (u.gotoFirstFile())
 * {
 * do
 * {
 * QString filename;
 * QDateTime dt;
 * CPPUNIT_ASSERT(u.getCurrentFileInfo(filename, &dt));
 *
 * QBuffer raw;
 * raw.open(IO_WriteOnly);
 * int method;
 * unsigned long crc, uncompressed_size;
 * CPPUNIT_ASSERT(u.getCurrentFileRaw(raw, method,
 * crc, uncompressed_size));
 * raw.close();
 * raw.open(IO_ReadOnly);
 * CPPUNIT_ASSERT(z.storeFileRaw(filename,
 * raw, dt, method, crc, uncompressed_size));
 * filescount++;
 * }
 * while (u.gotoNextFile());
 * }
 *
 * z.close();
 * u.close();
 * zipFile.close();
 * CPPUNIT_ASSERT(zipFile.open(IO_WriteOnly));
 * zipFile.writeBlock(newZip.buffer());
 * }
 */

QDomDocument upodt::analysis(QString &fileN) {
    QUnZip uz;
    QFile f(fileN);
    bool result = false;
    if (!f.open(QIODevice::ReadWrite)) { return QDomDocument(); }
    if (!uz.open(&f)) { return QDomDocument(); }
    if (!uz.locateFile("settings.xml", true)) { return QDomDocument(); }

    uz.gotoFirstFile();
    QString name, word1, word2;
    do {
        uz.getCurrentFileInfo(name, NULL);
        if (!name.endsWith("/") || !name.endsWith("\\")) {
            QBuffer b;
            bool ok;
            b.open(QIODevice::ReadWrite);
            ok = uz.getCurrentFile(b);
            b.close();
            if (ok && name == "settings.xml") {
                b.open(QIODevice::ReadOnly);
                QTextStream st(&b);
                QString all = st.readAll();
                qDebug() << unRO(all /*It doesn't need*/, true, all);
                b.close();
            }
        }
    } while (uz.gotoNextFile());
    f.close();
}

upodt* upodt::instance() {
    if (!instance_)
        instance_ = new upodt();
    return instance_;
}

upodt* upodt::instance_ = NULL;
