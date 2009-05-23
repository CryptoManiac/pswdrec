#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include "messengers/messengers.h"
#include "messengers/psi.h"
#include "messengers/kopete.h"
#include "messengers/sim.h"
#include "messengers/mdc.h"
#include "kftpgrabber.h"
#include "mail/kmail.h"

#include "systeminfo.h"

#include <QtXml/QDomDocument>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    getSystemInfo();

    /*   psi* p = new psi();
     * QString pass;
     * for (int i = 0;i<p->decoded.count();i++)
     * pass += p->decoded.at(i) + '\n';
     * ui->textEdit->setText(pass);
     * free(p);
     * pass.clear();
     *
     */
    /*QString pass;
    kopete* kk = new kopete();
      for (int i = 0;i<kk->decoded.count();i++)
      pass += kk->decoded.at(i) + '\n';
      ui->textEdit_2->setText(pass);
      free(kk);
      pass.clear();//*/


    /*
     * kftpgrabber * o = new kftpgrabber();
     *
     * kmail* km = new kmail();
     * for (int i = 0;i < km->decoded.count();i++)
     * pass += km->decoded.at(i) + '\n';
     * ui->textEdit_5->setText(pass);
     * free(km);
     * pass.clear();*/

    Parser(sim::instance()->decoded, ui->textBrowser_2);
    Parser(mdc::instance()->decoded, ui->textBrowser_3);
    qDebug() << kopete::instance()->decoded.toString();
    Parser(kopete::instance()->decoded, ui->textBrowser_4);

}

void MainWindow::Parser(QDomDocument qDoc, QTextBrowser *qBrwsr)
{
    QDomNode nRoot = qDoc.documentElement().firstChild();

    while (!nRoot.isNull()){

        for (int i = 0;i < nRoot.childNodes().count();i++) {
            QString sInfo;
            sInfo += "<b>" + nRoot.childNodes().at(i).toElement().tagName() + ": </b>";
            sInfo += nRoot.childNodes().at(i).toElement().text();
            qBrwsr->insertHtml(sInfo + " ");
        }
        qBrwsr->insertHtml("<br>");
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