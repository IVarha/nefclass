#include "rule.h"
#include <algorithm>


bool Rule::operator==(const Rule & other)
{
    bool b1 = true;


    if (weights.size() != other.weights.size())return false;

    for (int i = 0; i < weights.size();i++) {
        b1 = b1 & (weights[i] == other.weights[i]);
    }
    if (this->outWeights.size() == 0 && other.outWeights.size() == 0) {

    }
    else
    {

        b1 = b1 & equal(this->outWeights.begin(), this->outWeights.begin(),
            other.outWeights.begin());
    }
    return b1;
    return false;
}

Rule Rule::operator=(const Rule &)
{
    vector<Gauss> ve= vector<Gauss>();

    for (auto var = weights.begin();var!= weights.end();++var)
    {
        //Gauss g = var;
        ve.push_back(Gauss(var->getA(),var->getB()));
    }
    vector<double> v = vector<double>();
    for(auto var = outWeights.begin();var!=outWeights.end();++var)
    {
        
        v.push_back(*var);
    }
    Rule r =  Rule(ve);
    r.outWeights = v;
    r.ruleClass = ruleClass;
    return r;
}

Rule::Rule()
{
    weights = vector<Gauss>();
    outWeights = vector<double>();
}

Rule::Rule(vector<Gauss> w) {
    weights = vector<Gauss>();
    for(auto var = w.begin();var != w.end();++var)
    {
        Gauss g = *var;
        weights.push_back(g);
    }
}

Rule::~Rule()
{
}
//Evaluate output rule value of input
double Rule::activate1(vector<double> inp)
{
    int count = 0;

    double res = 1.0;
    for (auto x = inp.begin();x!= inp.end();++x) {
        res =  res*(weights.at(count).evaluate(*x));
        count++;
    }

    return res;
}

//Activate class output
vector<double> Rule::activate2(double inp)
{
    vector<double> v= vector<double>();

    for (auto var=outWeights.begin();var!= outWeights.end();++var)
    {
        double tmp = *var;
        v.push_back(tmp * inp);

    }
    return v;
}

void Rule::setOutWeight(vector<double> weight)
{
    this->outWeights = weight;
}

vector<double> Rule::getOutWeight()
{
    return outWeights;
}





void Rule::setRuleClass(int value)
{
    ruleClass = value;
}

int Rule::getRuleClass()
{
    return ruleClass;
}

vector<Gauss> Rule::getWeights()
{
    return weights;
}

void Rule::setWeights(vector<Gauss> w)
{
    weights = w;
}

void Rule::setOneOutput(int pos, double val)
{
    outWeights[pos] = val;
}



double Rule::getOneOutput(int pos)
{
    return outWeights[pos];
}

void Rule::setGauss(int pos, Gauss val)
{
    weights[pos] = val;
}

Gauss Rule::getGauss(int pos)
{

    return weights[pos];
}


