#ifndef FUZZYNEURALNETWORK_H
#define FUZZYNEURALNETWORK_H

#include <vector>
#include<gauss.h>
#include<rule.h>
#include<qcustomplot.h>
using namespace std;
class FuzzyNeuralNetwork
{
public:
    FuzzyNeuralNetwork();
    ~FuzzyNeuralNetwork();
    void trainGradient(vector<vector<double>> trainSet, vector<int> classes, int clCount, int inpDimension,
        int numOfWeights, double da, double db, double dc, double cinit, int kmax,int stopTime);
    vector<vector<Gauss>> evaluateWeightsFirst_T(vector<vector<double>> trainSet, int inpDimension, int numOfWeights);
    void trainWeights(vector<vector<double>> trainSet, vector<int> classes, int clCount, int inpDimension,
        int numOfWeights, double da, double db, double dc, double cinit, int kmax);
    vector<double> activate(vector<double> inp);
    double getDiffA(Rule a, vector<vector<double>> delta,double oR,double x,vector<int> classes,int pos);
    double getDiffB(Rule a, vector<vector<double>> delta, double oR, double x, vector<int> classes, int pos);
    double mase(vector<vector<double>> trainSet, vector<int> classes);
    void setTestSet(vector<vector<double>> tS, vector<int> tC);

    void drawGraph(QCustomPlot* qcp, int pos);

private:
    Gauss findMaxInWeights(vector<Gauss>& w, double x);
    vector<Rule> copyRules(vector<Rule>& copy);
    vector<vector<double>> testSet;
    vector<int> testClasses;
    Rule createAntecedent(vector<vector<Gauss>> w, vector<double> inp);
    void trainRules(vector<vector<double>> trainSet, vector<int> classes, int clCount, int inpDimension,
        int numOfWeights, int kmax, string trainAlgorithm);
    vector<Rule> rules;
    vector<vector<double>> interv;
    int clCnt;
};


#endif // FUZZYNEURALNETWORK_H
