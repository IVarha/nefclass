#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <fuzzyneuralnetwork.h>

#include <vector>
#include <set>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //first init
    da = 1.01;
    db = 1.01;
    dc = 1.01;
    rulC = 5;
    weight = 2;
    cv = 0.0;
    iter=4;
    showW = 0;
    fnn = nullptr;
    perc = 0.9;
    delim = "\t";
    redundant = 0;
    positOfClass = 0;

    testClasses = vector<int>();
    testSet = std::vector<vector<double>>();
}

MainWindow::~MainWindow()
{
    delete ui;
}




int vecSize;
int classCount;

void MainWindow::readFile(std::string str, bool read) {
    std::string line;
    std::ifstream myfile(str);
    if (read) {
        trainSet.clear();
        trainClasses.clear();
        trainClasses = vector<int>();
        trainSet = std::vector<vector<double>>();
    }
    else {
        testSet.clear();
        testClasses.clear();
        testClasses = vector<int>();
        testSet = std::vector<vector<double>>();
    }

    if (myfile.is_open())
    {
        int c = 0;
        vector<string> cs = vector<string>();

        while (getline(myfile, line))
        {
            //std::cout << line << '\n';
            QStringList ls;

            QString st = QString(line.c_str());
            QString del = QString(delim.c_str());
            ls = st.split(del);
            vector<double> tmp = vector<double>();
            for (int i = 0; i < ls.size(); i++) {
                if ((i == redundant) && redundant != -1) {

                }
                if ((i == positOfClass)){
                    QString str = ls.at(i);
                    cs.push_back(str.toStdString());
                }
                if (i != redundant && i != positOfClass) {
                    QString str = ls.at(i);
                    double r = str.toDouble();
                    tmp.push_back(r);
                }
            }
            trainSet.push_back(tmp);



        }


        vecSize = trainSet[0].size();
        set<string> stg(cs.begin(), cs.end());
        vector<string> tSet(stg.begin(), stg.end());
        classCount = stg.size();
        for (auto var=cs.begin();var!=cs.end();++var)
        {
            for (int j = 0; j < stg.size(); j++) {

                if (*var == tSet.at(j)) {
                    trainClasses.push_back(j);
                }
            }
        }
        myfile.close();
    }


}



void MainWindow::on_toolButton_clicked()
{
    QFileDialog dialog(this);

    dialog.setDirectory("c:\\TestData");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.exec();


    QString s = dialog.getOpenFileName();
    readFile(s.toStdString(), true);
    int cnt = trainSet.size() * (1-perc);
    for (int i = 0; i < cnt; i++) {
        testSet.push_back(trainSet.back());
        testClasses.push_back(trainClasses.back());
        trainSet.pop_back();
        trainClasses.pop_back();
    }


    int a = 1;
}

void MainWindow::on_pushButton_clicked()
{
    if (fnn == nullptr) {
        fnn = new FuzzyNeuralNetwork();

    }
    else {
        delete fnn;
        fnn = new FuzzyNeuralNetwork();
    }
    fnn->setTestSet(testSet, testClasses);
    fnn->trainGradient(trainSet, trainClasses, classCount, vecSize, weight, da,db,dc ,cv, rulC,iter);
    ui->spinShowWeight->setMaximum(vecSize);
}





void MainWindow::on_pushButton_2_clicked()
{
    fnn->drawGraph(ui->widget, showW);
}

void MainWindow::on_spinRules_valueChanged(int arg1)
{
    rulC = arg1;
}

void MainWindow::on_doubleDa_valueChanged(double arg1)
{
    da= arg1;
}


void MainWindow::on_doubleDb_valueChanged(double arg1)
{
    db=arg1;
}

void MainWindow::on_doubleDc_valueChanged(double arg1)
{
    dc = arg1;
}

void MainWindow::on_spinWeights_valueChanged(int arg1)
{
    weight = arg1;
}

void MainWindow::on_doubleDa_2_valueChanged(double arg1)
{
    cv = arg1;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    iter=arg1;
}

void MainWindow::on_spinShowWeight_valueChanged(int arg1)
{
    showW = arg1;
}

void MainWindow::on_spinPercentage_valueChanged(int arg1)
{
    perc = arg1/100;
}



void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    delim = arg1.toStdString();
}

void MainWindow::on_redundant_valueChanged(int arg1)
{
    redundant = arg1;
}

void MainWindow::on_positOfClass_valueChanged(int arg1)
{
    positOfClass = arg1;
}
