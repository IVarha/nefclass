#ifndef RULE_H
#define RULE_H
#include<vector>

#include<Gauss.h>
using namespace std;
class Rule
{
public:
    bool operator==(const Rule& other);
    Rule operator=(const Rule&);
    Rule();
    //Rule(vector<FuzzyWeight> w);
    Rule(vector<Gauss> w);
    ~Rule();
    double activate1(vector<double> inp);
    vector<double> activate2(double inp);
    void setOutWeight(vector<double> weight);
    vector<double> getOutWeight();
    void setRuleClass(int value);
    int getRuleClass();
    vector<Gauss> getWeights();
    void setWeights(vector<Gauss> w);
    void setOneOutput(int pos, double val);
    double getOneOutput(int pos);
    void setGauss(int pos,Gauss val);
    Gauss getGauss(int pos);

    //const string BEST_PER_CLASS = "BEST_PER_CLASS";
    //const string BEST = "BEST";
private:
    vector<Gauss> weights;
    vector<double> outWeights;
    int ruleClass;
};
#endif
