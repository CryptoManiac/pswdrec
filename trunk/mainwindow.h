#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtXml/QDomDocument>
#include <QTextBrowser>

#include "messengers/messengers.h"
#include "messengers/psi.h"
#include "messengers/kopete.h"
#include "messengers/sim.h"
#include "messengers/mdc.h"
#include "messengers/licq.h"
#include "messengers/alicq.h"
#include "messengers/pidgin.h"
#include "messengers/gajim.h"
#include "messengers/sipcom.h"
#include "messengers/saje.h"
#include "messengers/ayttm.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void getSystemInfo();
private:
    Ui::MainWindow *ui;

void Parser(QDomDocument qDoc, QTextBrowser *qBrwsr);

private slots:
    void on_pushButton_clicked();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
