#include<iostream>
#include"include/vector.h"
#include"include/fcn.h"



int main()
{
    Vector v;
    Vector v2;

    Point p = {1,1};
    Point p2= {0,2};
    Point p3= {3,3};
    Point p4= {4,4};
    Point p5 ={5,5};



    v2.push_back(p);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);


    //v.push_back(p1);



    Function f(v) ,g(v2);
    v.sort();
    v.print();

    f(2.25);
    //f*2;
    //f.find_zeros();
    f.fcnModifier(fonction_mono);
    //f.values.print();
    //f.surface(0,2,0.25);


    //v.lin_interpol(2);
    //surface(1,3);
    //angularVector;
    //v.angular_interpol(1.5);

    //v.find_zeros();






}
