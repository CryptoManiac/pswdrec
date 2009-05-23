#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QWidget>
#include <QDebug>
#include <QDesktopWidget>

#define version "0.03"
//#define codename Anna //the first release will be 0.1 // Love you my dear!

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    QWidget *desktop = QApplication::desktop();
    int xCenter = desktop->x() + (desktop->width() / 2);
    int yCenter = desktop->y() + (desktop->height() / 2);

    int windowWidth = w.width();
    int windowHeight = w.height();
    w.setGeometry( xCenter - (windowWidth / 2), yCenter - (windowHeight / 2), windowWidth, windowHeight );
    w.setFixedSize(w.width(), w.height());
    w.setWindowTitle("[PswDRec] - [v." + QString(version) + "]");

    w.show();
    return a.exec();
}
