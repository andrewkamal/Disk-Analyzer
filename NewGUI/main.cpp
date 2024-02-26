#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <newmain.h>
#include <string>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    char* name ="/home";

    newmain newm;
    newm.run(name);


    MainWindow x;
    x.show();

    return a.exec();
}


