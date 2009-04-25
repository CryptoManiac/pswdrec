#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QWidget>
#include <QDebug>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
QWidget *desktop = QApplication::desktop();
            int xCenter = desktop->x() + (desktop->width() / 2);
            int yCenter = desktop->y() + (desktop->height() / 2);

            int windowWidth = w.width();
            int windowHeight = w.height();
            w.setGeometry( xCenter - (windowWidth / 2), yCenter - (windowHeight / 2), windowWidth, windowHeight );
            w.setFixedSize(w.width(),w.height());

    w.show();
    return a.exec();
}
