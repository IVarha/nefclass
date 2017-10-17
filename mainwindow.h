#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>
#include <fuzzyneuralnetwork.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_toolButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_spinRules_valueChanged(int arg1);

    void on_doubleDa_valueChanged(double arg1);

    void on_doubleDb_valueChanged(double arg1);

    void on_doubleDc_valueChanged(double arg1);

    void on_spinWeights_valueChanged(int arg1);

    void on_doubleDa_2_valueChanged(double arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_spinShowWeight_valueChanged(int arg1);

    void on_spinPercentage_valueChanged(int arg1);

    void on_lineEdit_textEdited(const QString &arg1);

    void on_redundant_valueChanged(int arg1);

    void on_positOfClass_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    void readFile(std::string str,bool read);
    int rulC;
    int weight;
    double da;
    double db;
    double dc;
    double cv;
    int iter;
    int showW;
    FuzzyNeuralNetwork* fnn;
    double perc;
    vector<vector<double>> trainSet;
    vector<int> trainClasses;
    vector<vector<double>> testSet;
    vector<int> testClasses;
    string delim;
    int redundant;
    int positOfClass;
};
#endif // MAINWINDOW_H
