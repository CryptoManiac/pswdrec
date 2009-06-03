#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


#include "kftpgrabber.h"
#include "mail/kmail.h"

#include "google/ggadgets.h"
#include "mysqladm.h"
#include "systeminfo.h"

#include "common.h"


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    getSystemInfo();

    /*
     * kftpgrabber * o = new kftpgrabber();
     */


    Parser(sim::instance()->decoded, ui->textBrowser_2);
    Parser(mdc::instance()->decoded, ui->textBrowser_3);
    Parser(kopete::instance()->decoded, ui->textBrowser_4);
    Parser(licq::instance()->decoded, ui->textBrowser_5);
    Parser(alicq::instance()->decoded, ui->textBrowser_6);
    Parser(pidgin::instance()->decoded, ui->textBrowser_7);
    Parser(gajim::instance()->decoded, ui->textBrowser_8);
    Parser(sipcom::instance()->decoded, ui->textBrowser_9);
    Parser(saje::instance()->decoded, ui->textBrowser_10);
    Parser(ggadgets::instance()->decoded, ui->textBrowser_11);
    Parser(mysqladm::instance()->decoded, ui->textBrowser_12);
    Parser(ayttm::instance()->decoded, ui->textBrowser_13);
    Parser(psi::instance()->decoded, ui->textBrowser_14);
    Parser(kmail::instance()->decoded, ui->textBrowser_15);
}

void MainWindow::Parser(QDomDocument qDoc, QTextBrowser *qBrwsr)
{
    QDomNode nRoot = qDoc.documentElement().firstChild();

    while (!nRoot.isNull()){
    if (nRoot.childNodes().count() > 0){
        for (int i = 0;i < nRoot.childNodes().count();i++) {
            QString sInfo;
            sInfo += "<b>" + nRoot.childNodes().at(i).toElement().tagName() + ": </b>";
            sInfo += Qt::escape(nRoot.childNodes().at(i).toElement().text());
            qBrwsr->insertHtml(sInfo + " ");
        }
            qBrwsr->insertHtml("<br>");
        }
        nRoot = nRoot.nextSiblingElement();
    }
}

void MainWindow::getSystemInfo() {
    QDomDocument sysInfo = SystemInfo::instance()->collect();

    QDomElement root = sysInfo.firstChildElement();
    for (int i = 0;i < root.childNodes().count();i++) {
        QString sInfo;
        sInfo += "<b>" + root.childNodes().at(i).toElement().tagName() + ": </b>";
        sInfo += root.childNodes().at(i).toElement().text() + "<br>";
        ui->textBrowser->insertHtml(sInfo);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionExit_triggered() {
    exit(0);
}

void MainWindow::on_actionAbout_triggered() {

}
