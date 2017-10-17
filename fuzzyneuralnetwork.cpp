#include "fuzzyneuralnetwork.h"


#include "gauss.h"
#include "rule.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
using namespace std;
FuzzyNeuralNetwork::FuzzyNeuralNetwork()
{
}


FuzzyNeuralNetwork::~FuzzyNeuralNetwork()
{
}

void FuzzyNeuralNetwork::trainGradient(vector<vector<double>> trainSet, vector<int> classes, int clCount, int inpDimension,
    int numOfWeights, double da, double db, double dc, double cinit, int kmax,int stopTime)
{
    trainRules(trainSet, classes, clCount, inpDimension, numOfWeights, kmax, "BEST_PER_CLASS");
    trainWeights(trainSet, classes, clCount, inpDimension, numOfWeights, da,db,dc,cinit, stopTime);



}

vector<vector<Gauss>> FuzzyNeuralNetwork::evaluateWeightsFirst_T(vector<vector<double>> trainSet, int inpDimension, int numOfWeights) {
    vector<vector<double>> interval = vector<vector<double>>();
    //count first

    for (int i = 0;i < trainSet.at(0).size(); i++) {
        vector<double> tmp = vector<double>();
        for (auto var = trainSet.begin();var!=trainSet.end();++var)
        {
            tmp.push_back((*var).at(i));
        }

        vector<double > td = vector<double>();
        td.push_back(*min_element(tmp.cbegin(), tmp.cend()));
        td.push_back(*max_element(tmp.cbegin(), tmp.cend()));

        interval.push_back(td);
    }

    interv = interval;
    //Evaluate Weights first
    vector<vector<Gauss>> weights = vector<vector<Gauss>>();
    for (int i = 0; i< inpDimension;i++) {
        double delta = (interval.at(i).at(1) - interval.at(i).at(0)) / (numOfWeights-1);
        vector<Gauss> fwOne = vector<Gauss>();

        for (int j = 0; j < numOfWeights;j++) {
            Gauss fw = Gauss(interval.at(i).at(0) + delta*(j),
                delta);
            fwOne.push_back(fw);
        }
        weights.push_back(fwOne);
    }
    return weights;


}


void FuzzyNeuralNetwork::trainWeights(vector<vector<double>> trainSet, vector<int> classes, int clCount, int inpDimension,
    int numOfWeights, double da, double db, double dc, double cinit, int stopTime)
{
    //open file for results
    ofstream file1 = ofstream();
    file1.open("mapeChanges.csv");

    //Pre-set default output weights
    for (unsigned long i = 0; i < rules.size(); i++) {
        vector<double> tw = vector<double>();
        for (int j = 0; j < clCnt; j++) {
            tw.push_back(0.0);
        }
        tw[rules[i].getRuleClass()] = 1.0;
        rules[i].setOutWeight(tw);
    }


    double ma= 1;
    //calculate pre-set Ha and Hb

    vector<vector<double>> yv = vector<vector<double>>();
    for(auto var = interv.begin();var!=interv.end();++var){
       vector<double> val = vector<double>();

       vector<double> t = *var;
       double ya = (t[1] - t[0]) * 0.05;
       double yb = (t[1] - t[0]) * 0.05;
       val.push_back(ya);
       val.push_back(yb);
       yv.push_back(val);
       
    }


    double ew = 0;


    for (int i = 0;i < trainSet.size();i++) {
        //delta.push_back(vector<double>());
        vector<double> tr = this->activate(trainSet[i]);
        for (int j = 0;j < tr.size();j++) {
            if (j == (classes[i] - 1)) {
                ew += ((1 - tr[j])*(1 - tr[j]));
                //delta[i].push_back(1 - tr[j]);
            }
            else {
                ew += ((0 - tr[j])*(0 - tr[j]));

            }
        }
    }
    ew = ew / trainSet.size();

    double yo = cinit;

    //double yw = 1;
    int cnt = 0;
    double ys = dc;
    while (cnt<=stopTime) {//need to add stop criterio
        //vector inp
        //reEvaluate delta
        vector<vector<double>> yw = vector<vector<double>>();
        for (auto var=yv.begin();var!=yv.end();++var)
        {
            vector<double> val = vector<double>();
            vector<double> t2 = *var;
            double ya = t2[0]* (1/(1+da*cnt));
            double yb = t2[1] * (1 / (1 + db*cnt));
            val.push_back(ya);
            val.push_back(yb);
            yw.push_back(val);
        }
        yo = ys * (1 / (1 + dc*cnt));

        //evaluate delta value(ti - net(i)) and tmp values for Da and Db
        vector<vector<double>> delta = vector<vector<double>>();

        
        vector<double> tval = vector<double>(clCount,0.0);
        for (unsigned long i = 0;i < trainSet.size();i++) {
            delta.push_back(vector<double>());
            vector<double> tr = this->activate(trainSet[i]);
            for (unsigned long j = 0;j < tr.size();j++) {
                if (j == (unsigned long)(classes[i])) {
                    auto x = 1 - tr[j];
                    delta[i].push_back(x);
                    tval[j] += x;
                }
                else {
                    delta[i].push_back(0 - tr[j]);
                }
            }
        }

        //Calculate outputs of rules
        vector<vector<double>> oR = vector<vector<double>>();

        for (unsigned long i = 0;i < (unsigned long)trainSet.size();i++) {

            oR.push_back(vector<double>());
            for(auto var=rules.begin(); var!=rules.end(); ++var)
            {
                Rule r = *var;
                oR[i].push_back( r.activate1(trainSet[i]));
            }
        }

        // output previous value
        vector<Rule> rulv = rules;
        ma = mase(trainSet, classes);
        file1 << cnt << ';' << ma << ";" << mase(testSet,testClasses)<<endl;
        //calculate delt
        

    
            vector<Rule> tRules = copyRules(rules);
        
        for (unsigned long i = 0;i < trainSet.size();i++) {
            rulv = vector<Rule>();
            int khkl=i;
            for (unsigned long k = 0; k < rules.size();k++) {

                Rule r = Rule();
                int cl = rules[k].getRuleClass();
                vector<double> ow = rules[k].getOutWeight();
                vector<Gauss> gau = vector<Gauss>();
                r.setRuleClass(cl);
                for (int j = 0;j < inpDimension;j++) {
                    double a = rules[k].getGauss(j).getA();
                    double b = rules[k].getGauss(j).getB();
                    //GRADIENTS
                    double deltaA = (-4)*(oR[i][k]) * /*tval[classes[i]]*/ delta[i][classes[i]] * rules[k].getOneOutput(classes[i]) * (trainSet[i][j] - a) / (b*b);

                    double deltaB = (-4)*(oR[i][k]) * /*tval[classes[i]]*/delta[i][classes[i]] * rules[k].getOneOutput(classes[i]) * (trainSet[i][j] - a)*(trainSet[i][j] - a) / (b*b*b);
                    a = a - yw[j][0] * deltaA;
                    b = b - yw[j][1] * deltaB;
                    Gauss g = Gauss(a, b);
                    //this->inpRuleWeights[k].setGauss(j, g);
                    //cout << inpRuleWeights[k].getGauss(j).getA();
                    gau.push_back(g);

                }
                double y = rules[k].getOneOutput(cl);
                double dy3 = 0.0 - (delta[i][rules[k].getRuleClass()] * oR[i][k]);
                y = y - yo*dy3;
                ow[cl] = y;
                rules[k].setOneOutput(cl, y);
                r.setOutWeight(ow);
                r.setWeights(gau);
                rulv.push_back(r);


            }
            this->rules.clear();
            this->rules = rulv;
            delta.clear();
            oR.clear();


            //finish
        }
        cnt++;


    }
    file1.close();


}





/*
void FuzzyNeuralNetwork::trainWeights(vector<vector<double>> trainSet, vector<int> classes, int clCount, int inpDimension,
    int numOfWeights,  double da, double db, double dc, double cinit, int stopTime)
{
    //open file for results
    ofstream file1 = ofstream();
    file1.open("mapeChanges.csv");


    for (int i = 0; i < inpRuleWeights.size(); i++) {
        vector<double> tw = vector<double>();
        for (int j = 0; j < clCnt; j++) {
            tw.push_back(0.0);
        }
        tw[inpRuleWeights[i].getRuleClass()] = 1.0;
        inpRuleWeights[i].setOutWeight(tw);
    }

    double ma= 1;
    //calculate gamma
    vector<vector<double>> yv = vector<vector<double>>();
    for(auto var = interv.begin();var!=interv.end();++var){
       vector<double> val = vector<double>();

       vector<double> t = *var;
       double ya = (t[1] - t[0]) * 0.05;
       double yb = (t[1] - t[0]) * 0.05;
       val.push_back(ya);
       val.push_back(yb);
       yv.push_back(val);
    }


    double ew = 1;


    for (int i = 0;i < trainSet.size();i++) {
        //delta.push_back(vector<double>());
        vector<double> tr = this->activate(trainSet[i]);
        for (int j = 0;j < tr.size();j++) {
            if (j == (classes[i] - 1)) {
                ew += ((1 - tr[j])*(1 - tr[j]));
                //delta[i].push_back(1 - tr[j]);
            }
            else {
                ew += ((0 - tr[j])*(0 - tr[j]));

            }
        }
    }
    ew = ew / trainSet.size();

    double yo = cinit;

    double ya = 1;
    double yb = 1;
    //double yw = 1;
    int cnt = 0;
    double ys = dc;
    while (cnt<=stopTime) {//need to add stop criteri
        //vector inp
        vector<vector<double>> yw = vector<vector<double>>();
        for (auto var=yv.begin();var!=yv.end();++var)
        {
            vector<double> val = vector<double>();
            vector<double> t2 = *var;
            double ya = t2[0]* (1/(1+da*cnt));
            double yb = t2[1] * (1 / (1 + db*cnt));
            val.push_back(ya);
            val.push_back(yb);
            yw.push_back(val);
        }
        yo = ys * (1 / (1 + dc*cnt));


        vector<vector<double>> delta = vector<vector<double>>();

        for (int i = 0;i < trainSet.size();i++) {
            delta.push_back(vector<double>());
            vector<double> tr = this->activate(trainSet[i]);
            for (int j = 0;j < tr.size();j++) {
                if (j == (classes[i])) {
                    delta[i].push_back(1 - tr[j]);
                }
                else {
                    delta[i].push_back(0 - tr[j]);
                }
            }
        }
        vector<vector<double>> oR = vector<vector<double>>();


        for (int i = 0;i < trainSet.size();i++) {

            oR.push_back(vector<double>());
            for(auto var=inpRuleWeights.begin(); var!=inpRuleWeights.end(); ++var)
            {
                Rule r = *var;
                oR[i].push_back( r.activate1(trainSet[i]));
            }
        }

        // init cult
        vector<Rule> rulv = inpRuleWeights;
        ma = mase(trainSet, classes);
        file1 << cnt << ';' << ma << ";" << mase(testSet,testClasses)<<endl;
        //calculate delt
        for (int i = 0;i < trainSet.size();i++) {
            rulv = vector<Rule>();
            for (int k = 0; k < inpRuleWeights.size();k++) {

                Rule r = Rule();
                int cl = inpRuleWeights[k].getRuleClass();
                vector<double> ow = inpRuleWeights[k].getOutWeight();
                vector<Gauss> gau = vector<Gauss>();
                r.setRuleClass(cl);
                for (int j = 0;j < inpDimension;j++) {
                    double a = inpRuleWeights[k].getGauss(j).getA();
                    double b = inpRuleWeights[k].getGauss(j).getB();
 double deltaA = (-4)*(oR[i][k]) * delta[i][classes[i]] * rules[k].getOneOutput(classes[i]) * (trainSet[i][j] - a) / (b*b);
 
 double deltaB = (-4)*(oR[i][k]) * delta[i][classes[i]] * rules[k].getOneOutput(classes[i]) * (trainSet[i][j] - a)*(trainSet[i][j] - a) / (b*b*b);

                    a = a - yw[j][0] * deltaA;
                    b = b - yw[j][1] * deltaB;
                    Gauss g = Gauss(a, b);
                    //this->inpRuleWeights[k].setGauss(j, g);
                    //cout << inpRuleWeights[k].getGauss(j).getA();
                    gau.push_back(g);

                }
                double y = inpRuleWeights[k].getOneOutput(cl);
                double dy3 = 0.0 - (delta[i][inpRuleWeights[k].getRuleClass()] * oR[i][k]);
                y = y - 2*yo*dy3;
                ow[cl] = y;
                inpRuleWeights[k].setOneOutput(cl, y);
                r.setOutWeight(ow);
                r.setWeights(gau);
                rulv.push_back(r);


            }
            this->inpRuleWeights.clear();
            this->inpRuleWeights = rulv;
            //recalc delta probable should delete
            delta.clear();
            for (int i = 0;i < trainSet.size();i++) {
                delta.push_back(vector<double>());
                vector<double> tr = this->activate(trainSet[i]);
                for (int j = 0;j < tr.size();j++) {
                    if (j == (classes[i])) {
                        delta[i].push_back(1 - tr[j]);
                    }
                    else {
                        delta[i].push_back(0 - tr[j]);
                    }
                }
            }
            oR.clear();

            for (int i = 0;i < trainSet.size();i++) {

                oR.push_back(vector<double>());
                for (auto var = inpRuleWeights.begin();var!=inpRuleWeights.end();++var)
                {
                    Rule g = *var;
                    oR[i].push_back(g.activate1(trainSet[i]));
                }
            }
            //finish
        }
        cnt++;
        double tew = 0.0;
        for (int i = 0;i < trainSet.size();i++) {
            //delta.push_back(vector<double>());
            vector<double> tr = this->activate(trainSet[i]);
            for (int j = 0;j < tr.size();j++) {
                if (j == (classes[i])) {
                    tew += ((1 - tr[j])*(1 - tr[j]));
                    //delta[i].push_back(1 - tr[j]);
                }
                else {
                    tew += ((0 - tr[j])*(0 - tr[j]));
                }
            }
        }
        tew = tew / trainSet.size();
        ew = tew;

    }
    file1.close();


}
*/



//Evaluate output of NN
vector<double> FuzzyNeuralNetwork::activate(vector<double> inp)
{
    vector<vector<double>> tmp = vector<vector<double>>();
    vector<double> res = vector<double>();
    for (auto var=rules.begin();var!= rules.end();++var)
    {
        tmp.push_back(var->activate2(var->activate1(inp)));
    }

    for (int i = 0;i < clCnt;i++) {
        double max = tmp[0][i];
        for (int j = 1; j < tmp.size();j++) {
            if (tmp[j][i] > max) {
                max = tmp[j][i];
            }
        }
        res.push_back(max);
    }
    return res;
}

double FuzzyNeuralNetwork::getDiffA(Rule a, vector<vector<double>> delta, double oR, double x, vector<int> classes, int pos)
{
    double tmp = 0;
    int cnt = 0;




    for (int i = 0;i < classes.size();i++) {
        if (classes[i] == a.getRuleClass()) {
            tmp += (delta.at(i)[a.getRuleClass()]);
            cnt++;
        }
    }
    tmp = tmp *(-2)* oR* a.getOutWeight()[a.getRuleClass()]* a.getWeights()[pos].evaluate(x);
    double b = a.getWeights()[pos].getB();
    tmp = tmp*(x - a.getWeights()[pos].getA()) / (b*b);


    return tmp;
}

double FuzzyNeuralNetwork::getDiffB(Rule a, vector<vector<double>> delta, double oR, double x, vector<int> classes, int pos)
{
    //vector<double> s = delta[1];
    double tmp = 0;
    for (int i = 0;i < classes.size();i++) {
        if (classes[i] == a.getRuleClass()) {
            tmp += (delta[i][a.getRuleClass()]);
        }
    }
    tmp = tmp *(-2)* oR* a.getOutWeight()[a.getRuleClass()]*a.getWeights()[pos].evaluate(x);
    double b = a.getWeights()[pos].getB();
    double aa = a.getWeights()[pos].getA();
    tmp = tmp * (x - aa)*(x - aa) / (b*b*b);
    return tmp;
}

double FuzzyNeuralNetwork::mase(vector<vector<double>> trainSet, vector<int> classes)
{

    double res = 0;
    for (unsigned long i = 0; i < trainSet.size();i++)
    {
        vector<double> db = activate(trainSet[i]);
        int maxI = 0;
        double mx = db[0];
        for (unsigned long j = 0; j < db.size();j++) {
            if (db[j] > mx) {
                maxI = j;
                mx = db[j];
            }
        }

        if ((classes[i]) == maxI) {
            res += 1;
        }
    }

    return res/trainSet.size();
}

void FuzzyNeuralNetwork::setTestSet(vector<vector<double>> tS, vector<int> tC)
{
    testSet = tS;
    testClasses = tC;
}

void FuzzyNeuralNetwork::drawGraph(QCustomPlot * qcp, int pos)
{
    qcp->clearGraphs();
    srand(time(NULL));
    vector<QPen> pw = vector<QPen>();
    for (int i = 0; i < clCnt;i++) {
        int x = rand() % 255;
        int y = rand() % 255;
        int z = rand() % 255;
        pw.push_back(QPen(QColor(x,y,z)));
    }
    int N = 1000;
    double a = interv[pos][0];
    double b = interv[pos][1];
    double h = (b - a) / N;
    qcp->xAxis->setLabel("x");
    qcp->yAxis->setLabel("y");
    qcp->xAxis->setRange(a, b);
    QVector<double> x(N), y(N);
    for (int j = 0;j < 1000;j++) {

    }
    for (unsigned long i = 0; i < rules.size();i++) {

        qcp->addGraph();
        qcp->graph(i)->setPen(pw[rules[i].getRuleClass()]);
        QVector<double> x(N), y(N);
        for (int j = 0;j < 1000;j++) {
            x[j] = a + j*h;
            y[j] = rules[i].getWeights()[pos].evaluate(x[j]);
        }
        qcp->graph(i)->setData(x, y);
    }
    qcp->yAxis->setRange(0, 1);
    qcp->replot();
    //interv[pos][0]

}

Gauss FuzzyNeuralNetwork::findMaxInWeights(vector<Gauss>& w, double x)
{
    int max = 0;
    double maxtmp = w.at(0).evaluate(x);

    for (unsigned long i = 0;i < w.size();i++) {
        if (i>0) {
            double tmpVal = w.at(i).evaluate(x);
            if (tmpVal > maxtmp) {
                max = i;
                maxtmp = tmpVal;
            }
        }
    }
    return w.at(max);
    //return Gauss();
}

Rule FuzzyNeuralNetwork::createAntecedent(vector<vector<Gauss>> w, vector<double> inp)
{

    vector<Gauss> r = vector<Gauss>();
    for (unsigned long i = 0;i<inp.size();i++) {
        vector<Gauss> tmp = vector<Gauss>();


        for (unsigned long j = 0;j < w[i].size();j++) {
            tmp.push_back(*dynamic_cast<Gauss*>(&w[i][j]));
        }

        Gauss vecInp = findMaxInWeights(tmp, inp.at(i));
        r.push_back(vecInp);
    }
    Rule rule = Rule(r);
    return rule;
}

void FuzzyNeuralNetwork::trainRules(vector<vector<double>> trainSet, vector<int> classes, int clCount, int inpDimension, int numOfWeights, int kmax, string trainAlgorithm)
{
    vector<vector<Gauss>> weights = evaluateWeightsFirst_T(trainSet, inpDimension, numOfWeights);
    vector<Rule> antecedents = vector<Rule>();
    clCnt = clCount;
    for (unsigned long i = 0;i < trainSet.size();i++) {
        int cc = classes[i];
        Rule rule = createAntecedent(weights, trainSet[i]);
        //rule.setRuleClass(cc);
        if (find(antecedents.begin(), antecedents.end(), rule) == antecedents.end()) {
            antecedents.push_back(rule);
        }

    }

/*

    for each(vector<double> p in
        trainSet) {
        vector<Gauss> r();
        Rule rule = createAntecedent(weights, p);

        if (find(antecedents.begin(), antecedents.end(), rule) == antecedents.end()) {
            antecedents.push_back(rule);
        }
    }*/
        //init
        vector<vector<double>> actCountPerRule = vector<vector<double>>();
        for (int i = 0; i < antecedents.size();i++) {
            vector<double> t =  vector<double>();
            for (int j = 0;j<clCount;j++) {
                t.push_back(0.0);
            }
            actCountPerRule.push_back(t);
        }
        for (int i = 0; i<trainSet.size();i++) {

            int currCl = classes.at(i);
            for (int j = 0; j< antecedents.size();j++) {

                double x = actCountPerRule[j][currCl];
                x = x + antecedents.at(j).activate1(trainSet.at(i));
                actCountPerRule[j][currCl]= x;
            }

        }
        //Count Performance for output
        vector<double> performance = vector<double>();
        auto it = actCountPerRule.begin();

        for (Rule& ant :
        antecedents) {
            vector<double> cs = *it;
            auto v = max_element(cs.begin(), cs.end());
            int c = distance(cs.begin(),v);
            //int c = cs.indexOf(Collections.max(cs));
            ant.setRuleClass(c);
            double perf = cs.at(c);
            for (int i = 0;i< cs.size();i++) {
                if (i != c) {
                    perf -= cs.at(i);
                }
            }
            performance.push_back(perf);
            it++;
        }
        vector<Rule> resultRules = vector<Rule>();
        if (trainAlgorithm==("BEST")) {
            for (int i = 0;i<kmax; i++) {

                auto v = max_element(performance.begin(), performance.end());
                int R = distance(performance.begin(), v);
                //int R = performance.indexOf(Collections.max(performance));
                resultRules.push_back(antecedents.at(R));
                remove(performance.begin(), performance.end(), *v);
                remove(antecedents.begin(), antecedents.end(), antecedents[R]);

            }
        }
        else {
            if (trainAlgorithm=="BEST_PER_CLASS") {
                vector<vector<double>> ppc = vector<vector<double>>();
                vector<vector<Rule>> rpc = vector<vector<Rule>>();
                for (int i = 0;i< clCount;i++) {
                    ppc.push_back(vector<double>());
                    rpc.push_back(vector<Rule>());
                }
                for (int i = 0;i<antecedents.size();i++) {
                    Rule r = antecedents.at(i);

                    rpc.at(r.getRuleClass()).push_back(r);
                    ppc.at(r.getRuleClass()).push_back(performance.at(i));
                }

                for (int cl = 0; cl < clCount;cl++) {
                    vector<double> p = ppc.at(cl);
                    vector<Rule> r = rpc.at(cl);
                    for (int i = 0; i< kmax / clCount;i++) {
                        auto v = max_element(p.begin(), p.end());
                        if (v == p.end()) continue;
                        int R = distance(p.begin(),v);
                        resultRules.push_back(r.at(R));
                        p.erase(v);
                        r.erase(r.begin() + R);

                    }
                }

            }
        }
        rules = resultRules;
        /*List<Rule> r = new ArrayList<>();
        for (Rule rl :
        resultRules) {
            r.add((Rule)rl.clone());
        }
        inpRuleWeights = r;
        */

}

vector<Rule> FuzzyNeuralNetwork::copyRules(vector<Rule>& copy) {
    
    vector<Rule> res = vector<Rule>();
    for(unsigned long i = 0; i < copy.size();i++){
        Rule tmp= copy[i];
        res.push_back(tmp);
    }
    return res;
}

