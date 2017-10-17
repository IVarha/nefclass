#ifndef GAUSS_H
#define GAUSS_H


class Gauss
//	public FuzzyWeight
{
public:
    Gauss(double a, double b);
    Gauss();
    ~Gauss();
    bool operator==(const Gauss & other);
    Gauss operator=(const Gauss & other);
    // Inherited via FuzzyWeight
    double evaluate(double x);
    void setRuleClass(int cl);
    double getA();
    double getB();
private:
    double a;
    double b;
    int ruleClass;

    // Inherited via FuzzyWeight

};

#endif
