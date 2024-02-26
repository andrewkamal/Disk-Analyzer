#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QTableView>
#include <QtCore>
#include <fstream>
#include <iostream>
#include <string>
#include <QString>
#include <vector>
#include <cmath>


using namespace std;
QT_CHARTS_USE_NAMESPACE

string utility (string temp)
{
    string ret;
    for (int i=0; i<temp.size(); i++)
    {
        if (temp.at(i)=='/')
            continue;
        else
        {
            ret+=temp.at(i);
        }
    }
    return ret;

}
int generateRandom()
{
   int x = rand() % 256; // 0 to 255
    return x;
}

QChartView* createGraph(string file){
    ifstream infile;
    infile.open(file);
    string str, temp, name, size;
    int n, count = 0, r, g, b;
    srand (time(NULL));
    vector<string> s, i;
    QPieSeries *series;
    series = new QPieSeries();

    while((infile >> str) && (infile >> n)){
        temp = to_string(n);
        i.push_back(temp);
        QString qstr = QString::fromStdString(str);
        s.push_back((str));
        series->append(qstr, n);
    }

    infile.close();

         QChart *chart = new QChart();

         chart->addSeries(series);
         chart->setTitle("Disk Analyzer");
         chart->setTitleFont(QFont("Times", 28, QFont::Bold));
         chart->setAnimationOptions(QChart::AllAnimations);
         chart->legend()->setVisible(true);
         chart->legend()->setAlignment(Qt::AlignRight);

         QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);
           series->setPieSize(100);
         for(auto slice : (series->slices()))
         {
            name = s[count];
            size = i[count];
            QString qname = QString::fromStdString(name);
            QString qsize = QString::fromStdString(size);
            r = generateRandom();
            g = generateRandom();
            b = generateRandom();
            slice->setColor(QColor::fromRgb(r,g,b));
            slice->setLabel(QString( qname + " " + qsize + " " + "%1%").arg(100*slice->percentage(), 0, 'f', 1));
            count++;

         }
         return chartView;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    model = new QDirModel(this);
    model->setReadOnly(false);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

    ui->treeView->setModel(model);
    string file = "/home/andrewkamal/text";
    QChartView *chartView = createGraph(file);
    ui->verticalLayout_2->addWidget(chartView,0,0);


    QModelIndex index = model->index("/home/");

    //Add and Make Dir
    ui->treeView->expand(index);
    ui->treeView->scrollTo(index);
    ui->treeView->setCurrentIndex(index);
    ui->treeView->resizeColumnToContents(0);
    //Index Folders
    QString sPath = "/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(sPath);
    ui->treeView_2->setModel(dirmodel);
    //Index Files
    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel->setRootPath(sPath);
    ui->listView->setModel(filemodel);

    // this->menuBar()->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //Add dir
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid()) return;
    QString name = QInputDialog::getText(this,"Name", "Enter a name");
    if(name.isEmpty()) return;
    model->mkdir(index,name);
}

void MainWindow::on_pushButton_2_clicked()
{
    //Delete dir
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid()) return;
    if(model->fileInfo(index).isDir()) //dir
    {
        model->rmdir(index);
    }
    else //file
    {
        model->remove(index);
    }
}

void MainWindow::on_treeView_2_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(filemodel->setRootPath(sPath));

}

void MainWindow::on_treeView_2_doubleClicked(const QModelIndex &index)
{
    QString sendPath = dirmodel->fileInfo(index).absoluteFilePath();
    string updatedPath = sendPath.toStdString();
   if (updatedPath.find(check) != string::npos)
      {
       flag = true;
       check = updatedPath;
      }
    char* contvertPath = const_cast<char*>(updatedPath.c_str());
    if(flag)
    newm.run(contvertPath);
    string newPath = utility(updatedPath);
    string readPath = newm.cw + newPath + ".txt";
    cout << readPath << endl;
    QChartView *chartView = createGraph(readPath);
    qDeleteAll(ui->verticalLayout_2->children());  // not to crete new screens
    //Delete Content of the the Layout
    QLayoutItem* child;
    child=ui->verticalLayout_2->takeAt(0);
    while(child != 0)
    {
    ui->verticalLayout_2->removeWidget(child->widget());
    delete child;
    child=ui->verticalLayout_2->takeAt(0);
    }
    ui->verticalLayout_2->addWidget(chartView,0,0);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_4_clicked()
{
    QString boxPath = ui->lineEdit->text();
    string path = boxPath.toStdString();
    if (path.find(check) != string::npos)
    {
        flag = true;
        check = path;
     }
    char* contvertPath = const_cast<char*>(path.c_str());
    if(flag)
    newm.run(contvertPath);
    string newPath = utility(path);
    string readPath = newm.cw + newPath + ".txt";
    cout << readPath << endl;
    QChartView *chartView = createGraph(readPath);
    qDeleteAll(ui->verticalLayout_2->children());  // not to crete new screens
    //Delete Content of the the Layout
    QLayoutItem* child;
    child=ui->verticalLayout_2->takeAt(0);
    while(child != 0)
    {
    ui->verticalLayout_2->removeWidget(child->widget());
    delete child;
    child=ui->verticalLayout_2->takeAt(0);
    }
    ui->verticalLayout_2->addWidget(chartView,0,0);
}
