#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include "messengers.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  Messengers* m = new Messengers();
  m->QD();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}
