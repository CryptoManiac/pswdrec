#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtXml/QDomDocument>
#include <QTextBrowser>

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
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
