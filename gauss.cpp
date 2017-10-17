#include "gauss.h"
#include "math.h"

Gauss::Gauss(double a, double b)
{
    this->a = a;
    this->b = b;
}

Gauss::Gauss()
{

}


Gauss::~Gauss()
{
}

double Gauss::evaluate(double x)
{
    return exp(0-(pow(x - a, 2) / pow(b, 2)));
}

void Gauss::setRuleClass(int cl)
{
    ruleClass = cl;
}

double Gauss::getA()
{
    return a;
}

double Gauss::getB()
{
    return b;
}

bool Gauss::operator==(const Gauss & other)
{
    if (this->a == other.a && this->b == other.b) return true;
    return false;
}

Gauss Gauss::operator=(const Gauss & other)
{
    return Gauss(other.a,other.b);
}
