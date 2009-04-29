#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include "messengers/messengers.h"
#include "messengers/psi.h"
#include "messengers/kopete.h"
#include "messengers/sim.h"
#include "kftpgrabber.h"
#include "mail/kmail.h"

#include "systeminfo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    psi* p = new psi();
    QString pass;
    for (int i = 0;i<p->decoded.count();i++)
        pass += p->decoded.at(i) + '\n';
        ui->textEdit->setText(pass);
    free(p);
    pass.clear();

    kopete* kk = new kopete();
    for (int i = 0;i<kk->decoded.count();i++)
        pass += kk->decoded.at(i) + '\n';
        ui->textEdit_2->setText(pass);
        free(kk);
        pass.clear();

    ui->label_2->setText(SystemInfo::instance()->os());
    ui->label_4->setText(SystemInfo::instance()->localHostName_());
    ui->label_6->setText(SystemInfo::instance()->kernelVersion());
    sim * s = new sim();
    for (int i = 0;i < s->decoded.count();i++)
        pass += s->decoded.at(i) + '\n';
    ui->textEdit_4->setText(pass);
    free(s);
    pass.clear();

        kftpgrabber * o = new kftpgrabber();

        kmail* km = new kmail();
        for (int i = 0;i < km->decoded.count();i++)
        pass += km->decoded.at(i) + '\n';
        ui->textEdit_5->setText(pass);
        free(km);
    pass.clear();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionAbout_triggered()
{

}
