#ifndef FCN_H
#define FCN_H
#include <iostream>
#include"vector.h"




class Function
{
public:
    Function();
    Function(Vector v);

    Vector find_zeros() const;
    double lin_interpol(double toEval);
    double surface(double left, double right, double integral_pace );
    Vector fcnModifier(double (*fonction)(double) );
    Function operator+(double a);
    Function operator-(double a);
    Function operator*(const double a);
    double operator()(double a);
    Vector values;



private:

};
void fonction_multi( int begin, int end);
double fonction_mono(double y);


//inherite classe

class angularFunction: public Function
{
public:
    angularFunction();
    angularFunction(Vector a);
    int lin_interpol(double toEval);
};
#endif // FCN_H
