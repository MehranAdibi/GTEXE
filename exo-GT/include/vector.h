#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>


// defineinf a point
struct Point{
    double x;
    double y;
    Point operator* (double num) // * overload
    {
        Point p;
        p.x = p.x*num;
        p.y = p.y*num;
        return p;
    }

    bool operator == (const Point& b) // == overload
    {
        if(x == b.x && y == b.y)
            return true;
        else
            return false;
    }
};


// user-defined vector class
class Vector
{

public:

    Vector();
    ~Vector();
    Vector(int index);
    Vector& operator=(const Vector& a);
    Vector& operator+(const Vector& a);
    Vector(const Vector & arg);
    void print();
    int size() const;
    Point get(int index) const;
    void set(int index, Point val);
    int exists(double p);
    void insert(Point val);
    void push_back(Point data);
    double find(double toEval);
    void sort();
    int get_index(double p);
    int get_closest_value(Point val) const;
    int get_closest_value(double val) const;
    Point* arr;
    int current;
    int capacity;


private:
    void merge(int a, int b, int c);
    void mergesort(int a, int b);
};

#endif // VECTOR_H
