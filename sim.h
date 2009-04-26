#ifndef SIM_H
#define SIM_H

#include <QObject>

class sim : public QObject
{
public:
    sim();
    void findConfig();
    QList<QString> decoded;
private:
    QString decodePassword(const QString &hash);
};

#endif // SIM_H
