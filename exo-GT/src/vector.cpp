#include <iostream>
#include<math.h>
#include "../include/vector.h"
#include"thread"

// constructors
Vector::Vector()
{
    arr = new Point[1];
    capacity = 1;
    current = 0;
}

Vector::Vector(int s)
{
    arr = new Point[s];
    capacity = s;
    current = capacity;
}

Vector::Vector(const Vector & arg)
{
    arr = new Point[arg.size()];
    capacity = arg.size();

    int size = arg.size();
    for(int i = 0; i < size; ++i)
    {
        arr[i] = arg.get(i);
    }
    current = arg.current;
}
//destructor
Vector::~Vector()
{
    delete [] arr;
}




// operator overloads
Vector& Vector::operator+(const Vector& a)
{
    for(int i=0; i<a.size(); i++)
    {
        push_back(a.arr[i]);
    }
    return *this;
}

Vector& Vector::operator=(const Vector& a)
{
    if (this == &a) return *this;


    if (a.current <= capacity)
    {
        for (int index = 0; index < a.current; ++index)
        {
            arr[index] = a.arr[index];
            current = a.current;
            return *this;
        }
    }

    Point* p = new Point[a.current];

    for (int index = 0; index < a.current; ++index)
        p[index] = a.arr[index];

    delete[] arr;
    current = a.current;
    capacity = a.capacity;
    arr = p;
    return *this;
}


// print a vector to console
void Vector::print()
{
    int s = size();
    for (int i =0;i<s; ++i)
    {
        Point p = get(i);
        std::cout << "(" << p.x << "," << p.y << ") ";
    }
    std::cout << std::endl;
}


// get the size of the vector
int Vector::size() const
{
   return current;
}

// get the value of a specific index of the vector
Point Vector::get(int index) const
{
    if (index < current)
        return arr[index];
}

// set a point to a specific index
void Vector::set(int index, Point val)
{
    if (index < capacity)
        arr[index] = val;
    else
        std::cout << "out of bounds" << std::endl;
}

// check existing of a given 'x' in the set of pairs
int Vector::exists(double p)
{

    for (int i=0 ;i<size();i++)
    {

        if (arr[i].x== p)
        {
            std::cout<<"exists"<<std::endl;
            return i;
            break;
        }

     }
    return -1;
}

// add a new point to the vector (unordered)
void Vector::push_back(Point data)
{
    if (current == capacity)
    {
        Point* temp = new Point[2 * capacity];


        for (int i = 0; i < current; i++)
        {
            temp[i] = arr[i];
        }


        delete[] arr;
        capacity *= 2;
        arr = temp;
    }


    arr[current] = data;
    current++;
}

// it's an ordered push_back
void Vector::insert(Point val)
{
    if (current == capacity) {
        Point* temp = new Point[2 * capacity];


        for (int i = 0; i < current; i++) {
            temp[i] = arr[i];
        }


        delete[] arr;
        capacity *= 2;
        arr = temp;
    }
    if(current == 0 || val.x > arr[current-1].x )
    {
        push_back(val);
    }
    else
    {
        int i = get_closest_value(val);
        if (arr[i].x == val.x){return;}
        if (arr[i].x >= val.x)
        {
            for(int k=current-1; k>=i; k--)
            {
                arr[k+1]=arr[k];
            }
            arr[i]=val;
            current++;
        }
        else
        {
            i++;
            for(int k=current-1; k>=i; k--)
            {
                arr[k+1]=arr[k];
            }
            arr[i]=val;
            current++;
        }
    }
}

// uses linear interpolation to determine a 'y' for a given 'x'
// is used in find_zeros

double Vector::find(double toEval)
{

            Point a , b;

            sort();
            int left =get_closest_value(toEval);


            if(left == current - 1)
            {
                std::cout<<"out of bond"<<std::endl;


            }
            else
            {
                a= get(left);
                b= get (left +1);
                double m = (b.y-a.y)/(b.x-a.x);//slope
                double pp = a.y - m*a.x; // pickPoint
                std::cout<<m*toEval + pp<<std::endl;
                return m*toEval + pp;
            }
}

//sorting the vector with merge sort methode
void Vector::sort()
{
    mergesort(0,current-1);
}

int Vector::get_index(double p){
    int res = exists(p);
    if (res >=0)
    {
        return res;
    }
    else
    {
        insert({p, find(p)});
        get_index(p);
    }
}


int Vector::get_closest_value(double val) const
{
    int a=0;
    int b=size()-1;
    while(a<=b)
    {
        int mid=(a+b)/2;
        if(get(a).x >= val)
            return a;

        if(get(b).x <= val)
            return b;

        if(get(mid).x<=val && get(mid+1).x>val)
            return mid;

        if(get(mid).x>val)
            b=mid;

        if(get(mid).x<val)
            a=mid;

    }
}

// gets closest value <= of a given value of a point
int Vector::get_closest_value(Point val) const
{
    int a=0;
    int b=size()-1;
    while(a<=b)
    {
        int mid=(a+b)/2;
        if(get(a).x >= val.x)
            return a;

        if(get(b).x <= val.x)
            return b;

        if(get(mid).x<=val.x && get(mid+1).x>val.x)
            return mid;

        if(get(mid).x>val.x)
            b=mid;

        if(get(mid).x<val.x)
            a=mid;
    } 
}
// merge sort function
void Vector::merge(int l, int r, int m)
{
    int n1,n2,i,j,k;
    n1 = m - l + 1;
    n2 = r - m;

    Vector L(n1), R(n2);
    for(i=0;i<n1;i++)
    {
        L.set(i,get(l+i));

    }

    for(j=0;j<n2;j++)
    {
        R.set(j, get(m+j+1));

    }

    i=0,j=0;

    for(k=l;i<n1 && j<n2;k++)
    {
        if(L.get(i).x < R.get(j).x)
        {
            set(k,L.get(i));
            i++;
        }
        else
        {
            set(k,R.get(j));
            j++;
        }
    }

    while(i<n1)
    {
        set(k,L.get(i));
        k++;
        i++;
    }

    while(j<n2)
    {
        set(k,R.get(j));
        k++;
        j++;
    }
}

//
void Vector::mergesort(int l, int r)
{
    int m;
    if(l<r)
    {
        m = (l+r)/2;
        mergesort(l,m);
        mergesort(m+1,r);
        merge(l,r,m);

    }
}







