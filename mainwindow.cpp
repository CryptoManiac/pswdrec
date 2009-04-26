#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include "messengers.h"
#include "psi.h"
#include "kopete.h"
#include "systeminfo.h"
#include "sim.h"

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

        QString sysinf = "Distro: " + SystemInfo::instance()->os() + '\n';
    sysinf += "Hostname: " + SystemInfo::instance()->localHostName_();
    ui->textEdit_3->setText(sysinf);

    sim * s = new sim();
    for (int i = 0;i < s->decoded.count();i++)
        pass += s->decoded.at(i) + '\n';
    ui->textEdit_4->setText(pass);
    free(s);
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
