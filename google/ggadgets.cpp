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
//    QString qqq = "eF[n=94=BA=C7=FE=D7:Af=0F";
//     std::string value_str = UnescapeValue(qqq.toStdString());
//     std::string temp(value_str);
//    Decrypt(temp, &value_str);
//     qDebug() << value_str.data();

    root = decoded.createElement("ggadgets");
    decoded.appendChild(root);
    findConfig();
}

QString ggadgets::decode(QString hash) {
    QString result;
    std::string value_str = UnescapeValue(hash.toStdString());
    std::string temp(value_str);

    Decrypt(temp, &value_str);
    result = QString(value_str.data());
    return result;
}

void ggadgets::decoding(QFile &file){
    QDomDocument doc;
    doc.setContent(&file);
    QDomElement root = doc.documentElement();
    QString login, pass, other;
    QDomDocument oth;
    for (int i = 0; i<root.childNodes().count(); i++) {
        QDomElement temp = root.childNodes().at(i).toElement();
        if (temp.attribute("encrypted") == "1") {
            if (temp.attribute("name").toLower() == "password") {
                pass = decode(temp.text());
                pass = pass.mid(1, pass.length() - 2); //fucking quotes
            } else if (temp.attribute("name").toLower() == "username") {
                login = decode(temp.text());
                login = login.mid(1, login.length() - 2); //fucking quotes
            } else {
                other = decode(temp.text());
                other = other.mid(1, other.length() - 2); //fucking quotes
                QString tagName = temp.attribute("name").toLower();  //Make tagName lowercase
                tagName = tagName.at(0).toUpper() + tagName.mid(1, tagName.length() - 1); //Make tagName first char uppercase
                QDomElement tag = oth.createElement(tagName);
                oth.appendChild(tag);
                QDomText t = oth.createTextNode(other);
                tag.appendChild(t);
            }
        } else {
            if (temp.attribute("type") == "j") {
                if (temp.attribute("name").toLower() == "password") {
                    pass = temp.text();
                } else if (temp.attribute("name").toLower() == "username") {
                    login = temp.text();
                } else {
                    other = temp.text();
                    QString tagName = temp.attribute("name").toLower();  //Make tagName lowercase
                    tagName = tagName.at(0).toUpper() + tagName.mid(1, tagName.length() - 1); //Make tagName first char uppercase
                    QDomElement tag = oth.createElement(tagName);
                    oth.appendChild(tag);
                    QDomText t = oth.createTextNode(other);
                    tag.appendChild(t);
                }
            }
        }
    }
    createXML(login, pass, oth);
}

void ggadgets::createXML(QString login, QString pass, QDomDocument &opt){
    QDomElement q = decoded.createElement("Account");
    root.appendChild(q);
    QDomElement tag;
    QDomText t;

    if (!login.isEmpty()){
        tag = decoded.createElement("Login");
        q.appendChild(tag);
        t = decoded.createTextNode(login);
        tag.appendChild(t);
    }
    if (!pass.isEmpty()){
        tag = decoded.createElement("Password");
        q.appendChild(tag);
        t = decoded.createTextNode(pass);
        tag.appendChild(t);
    }

    if (!opt.isNull()){
        for (int i = 0;i < opt.childNodes().count();i++)
        {
            QDomElement el = opt.childNodes().at(i).toElement();
            q.appendChild(el);
        }
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
    foreach(QString s, dirListFiles(homeDir()+".google/gadgets-plasma/options", gadgets)){
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
