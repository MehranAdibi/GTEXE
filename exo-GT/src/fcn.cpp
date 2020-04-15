#include <iostream>
#include <math.h>
#include"../include/fcn.h"
#include "../include/vec.h"
#include<future>
#include<vector>



#define nbThread 6
// constructors
Function::Function()
{

}

Function::Function(Vector v)
{
    for(int i=0; i < v.size();i++)
    {
        values.insert(v.get(i));
    }
}

// operator overload
Function Function::operator+( double a)
{

   for(int j=0 ; j< values.size(); j++)
       values.arr[j].y+=a;
   return values;
}

Function Function::operator-( double a)
{
    for(int j=0 ; j< values.size(); j++)
        values.arr[j].y-=a;
    return values;

}
Function Function::operator*(const double a)
{
    for(int i =0 ; i< values.size();i++)
    {
        values.arr[i].y*=a;
    }
    return values;
}
double Function::operator()(double a)
{

    return lin_interpol(a);
}
// function to find existing and/or estimated zeros of a set
Vector Function::find_zeros() const
{
    double y_zero,m,pp;
    Point p;
    Vector zeros;
    int b = values.size();
    ///
    Vector zeros_in_set;
    for(int i = 0; i<b; ++i)
    {
        if(values.arr[i].y==0)
        {
           zeros_in_set.push_back(values.arr[i]);

        }

    }
    if(zeros_in_set.size()!=0)
    {
        std::cout<<"Zeros found in the set: "<<std::endl;
        zeros_in_set.print();

    }
    else{
        std::cout<<"No zeros found in the set."<<std::endl;
    }

    for(int i=0; i<b;++i)
    {


        if(values.arr[i].y<0 && values.arr[i+1].y>0)
        {
            m = (values.arr[i+1].y-values.arr[i].y)/(values.arr[i+1].x-values.arr[i].x);//slope

            pp = values.arr[i+1].y - m*values.arr[i+1].x; // pickPoint
            y_zero = -pp/m;
            p= {y_zero,0};
            zeros.push_back(p);

        }
        if(values.arr[i].y>0 && values.arr[i+1].y<0)
        {
            m = (values.arr[i+1].y-values.arr[i].y)/(values.arr[i+1].x-values.arr[i].x);

            pp = values.arr[i+1].y-m*values.arr[i+1].x;
            y_zero = -pp/m;
            p= {y_zero,0};
            zeros.push_back(p);
        }
    }
    std::cout<<"Estimated zeros of the function: "<<std::endl;
    zeros.print();
    return zeros,zeros_in_set;
}
 // linear interpolation
double Function::lin_interpol(double toEval)
{
        Point a , b;
        values.sort();
        int left = values.get_closest_value(toEval);

        if(left == values.size())
        {
            std::cout<<"out of bounds"<<std::endl;
        }
        else
        {
            a= values.get(left);
            b= values.get(left +1);
            double m = (b.y-a.y)/(b.x-a.x);//slope
            double pp = a.y - m*a.x; // pickPoint
            std::cout<<"Interpolation result for x = "<<toEval<<" : " << m*toEval + pp<<std::endl;
            return m*toEval + pp;
        }
}

// calculates the integral based on Trapezoidal rule

double Function::surface(double left, double right,double integral_pace = 0.5)
{


    Vector vds;
    double x_max, x_min;
    double surface=0;
    x_max = std::max(left,right);
    x_min = std::min(left,right);


    for (int i = values.get_index(x_min); i< values.get_index(x_max);i++)
    {
        if (values.arr[i+1].x - values.arr[i].x > integral_pace)
        {
            int pas =((values.arr[i+1].x - values.arr[i].x)/integral_pace);
            for(int j =0; j< pas+1; j++)
                vds.push_back({values.arr[i].x+j*integral_pace , lin_interpol(j*integral_pace + values.arr[i].x)});
        }
        else
            vds.push_back(values.arr[i]);
    }
    for (int k = 0; k<vds.size()-1; k++)
    {
        surface+=((vds.get(k+1).x - vds.get(k).x)*(vds.get(k+1).y + vds.get(k).y))/2;

    }
    std::cout<<"surface calculated with integration pace of \" "<<integral_pace<< " \" is: "<<surface<<std::endl;
    return surface;
}

// function pointer part

void fonction_multi(Vector& v , int begin, int end) // simple function representing 'g' in g(f(x))
{
    for (int i= begin ; i<end; i++)
    {
        v.arr[i].y+2;
    }
}
double fonction_mono(double y)
{
    return y+2;
}

//multithreaded function representing 'f' in g(f(x))
Vector Function::fcnModifier(double (*fonction)(double) )
{

    //*The vector is cut into several parts to be processed in parallel.
    // uses <vector>
    //**First methode:

    /*
    Vector v1;
    //int nbThread = 6;                    //nbthread defined 6 in preprocessor directives
    std::vector<std::thread> threads;
    int step = values.size() / nbThread;
    for (int i = 0; i < nbThread; ++i)
    {
        int begin = i * step;
        int end = (i + 1) * step;
        if (i == nbThread - 1)
        end = values.size();
        threads.emplace_back([&] ()
        {
        for(int j = begin; j < end;j++)
        {
            v1.push_back({ values.get(j).x , fonction(values.get(j).y) });
        }
        });
    }
    for (auto& thread : threads)
    {
        thread.join();
    }
    std::cout<<"Function modified to :"<<std::endl;
    v1.print();
    return v1;
*/


    //**second methode with std::async:


   /* Vector v1;

    std::vector<std::future<void>> futureResults;       //costume class template: Vec
    for ( int i=0 ; i<nbThread ; i++)
    {
        int begin = values.size()/nbThread;
        begin*=i;
        int end = values.size()/nbThread;
        end*=(i+1);
        if (end==nbThread - 1)
            end= values.size();
        futureResults.push_back(std::async(std::launch::async, fonction, std::ref(values), begin, end));
        std::cout<<typeid(futureResults).name()<<std::endl;

    }

    for (auto & futureRes : futureResults)
    {
        std::cout<<typeid(futureResults).name()<<std::endl;
        v1+=futureRes.get();        // operator + is overloaded
    }*/

    //**one thread base function:

    /*Vector v1;
    Point p;
    for(int i=0; i< values.size();i++)
    {

        p = { values.get(i).x , fonction(values.get(i).y) };
        v1.push_back(p);

    }


    v1.print();
    return v1;*/
}


//angularFunction
// inherits "Function" class

//constructor
angularFunction::angularFunction()
{

}

angularFunction::angularFunction(Vector v)
{

    for(int i=0; i < v.size();i++)
    {
        values.insert(v.get(i));
    }
}

// angle interpolation
// replaces lin_interpol function in mother class
int angularFunction::lin_interpol(double toEval)
{
    Point a , b;

    values.sort();
    int left = values.get_closest_value(toEval);
    int angle1, angle2;
    int cy;
    long double m;
    double coef1,coef2;

    if(left == values.current - 1)
    {
        std::cout<<"out of bond"<<std::endl;


    }
    else
    {
        a= values.get(left);
        b= values.get (left +1);
        angle1 = (int)a.y;
        angle2 = (int)b.y;

        if(angle1<0)
            angle1=360+ angle1;
        else
            angle1%=360;

        if(angle2<0)
            angle2=360+angle2;
        else
            angle2%=360;

        if(a.y>b.y)
        {
           cy= Function::lin_interpol(toEval)+180;
           std::cout<<"cy : "<<cy<<std::endl;
        }
        if(b.y>a.y)
            cy =Function::lin_interpol(toEval);
        std::cout<<"cy : "<<cy<<std::endl;

   }

}
//





