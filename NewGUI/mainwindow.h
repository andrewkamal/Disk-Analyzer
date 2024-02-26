#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDirModel>
#include <QtCore>
#include <QtGui>
#include <QInputDialog>
#include <QFileSystemModel>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QConicalGradient>
#include "newmain.h"
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    string check;
    bool flag;
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_treeView_2_clicked(const QModelIndex &index);
    void on_treeView_2_doubleClicked(const QModelIndex &index);
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QDirModel *model;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
    newmain newm;


protected:
//    void paintEvent(QPaintEvent *e);

};

#endif // MAINWINDOW_H
