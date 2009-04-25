#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include "messengers.h"
#include "psi.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  /*Messengers* m = new Messengers();
  ui->label->setText(m->QD()); */
    psi* p = new psi();
    QString pass;
    for (int i = 0;i<p->decoded.count();i++)
        pass += p->decoded.at(i) + '\n';
        ui->textEdit->setText(pass);

    free(p);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}
