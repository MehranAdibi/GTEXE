#include "../include/vec.h"
#include <iostream>

// template Vec class based on Vector class (vector.cpp)




//base constructor ex:  Vec<type> v;
template <class T>
Vec<T>::Vec()
{
    arr = new T[1];
    capacity = 1;
    current = 0;
}

;
template <class T>
Vec<T>::Vec(int size)
{
    arr = new T[size];
    capacity = size;
    current = 0;
}

// Assign a vector to another ex:  Vec newV= oldV
template <class T>
Vec<T>& Vec<T>::operator=(const Vec<T>& a)
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

    T* p = new T[a.current];

    for (int index = 0; index < a.current; ++index)
        p[index] = a.arr[index];

    delete[] arr;
    current = a.current;
    capacity = a.capacity;
    arr = p;
    return *this;
}


template <class T>
int Vec<T>::size() const
{
   return current;
}
template <class T>
int Vec<T>::begin() const
{
   return 0;
}

template <class T>
int Vec<T>::end() const
{
   return capacity+1;
}

template <class T>
T Vec<T>::get(int index) const
{
    if (index < current){
        T tmp = arr[index];
        return tmp;}
}


template <class T>
void Vec<T>::set(int index, T val)
{
    if (index < current)
        arr[index] = val;
    else
        std::cout << "out of bounds" << std::endl;
}

template <class T>
Vec<T>::Vec(const Vec & arg)
{
    int size = arg.size();
    arr = new T[size];
    capacity = size;
    current = 0;
    for(int i = 0; i < size; ++i)
    {
        push_back(arg.arr[i]);
    }
}

template <class T>
void Vec<T>::print()
{
    int s = size();
    for (int i =0;i<s; ++i)
    {
        std::cout << get(i) << " ";
    }
    std::cout << std::endl;
}

template<class T>
void Vec<T>::push_back(T data)
{
    if (current == capacity) {
        T* temp = new T[2 * capacity];


        for (int i = 0; i < capacity; i++) {
            temp[i] = arr[i];
        }


        delete[] arr;
        capacity *= 2;
        arr = temp;
    }


    arr[current] = data;
    current++;
}

template<class T>
void Vec<T>::insert(T val)
{
    if (current == capacity) {
        T* temp = new T[2 * capacity];


        for (int i = 0; i < capacity; i++) {
            temp[i] = arr[i];
        }


        delete[] arr;
        capacity *= 2;
        arr = temp;
    }
    if(val > arr[current-1] || current == 0)
    {
        push_back(val);
    }
    else
    {
        int i = get_closest_value(val);
        if (arr[i] == val){return;}
        if (arr[i] >= val)
        {
            for(int k=current-1; k>=i; k--){
                arr[k+1]=arr[k];
            }
            arr[i]=val;
            current++;
        }
        else
        {
            i++;
            for(int k=size()-1; k>=i; k--){
                arr[k+1]=arr[k];
            }
            arr[i]=val;
            current++;
        }
    }
}

template<class T>
int Vec<T>::get_closest_value(T val) const
{
    int a=0;
    int b=size()-1;
    while(a<b)
    {
        int mid=(a+b)/2;
        T tmpa = get(a);
        T tmpb = get(b);
        T tmpmid = get(mid);
        if(tmpa==val){return a;}
        if(tmpb==val){return b;}
        if(tmpmid<=val && get(mid+1)>val) return mid;
        if(tmpmid>val)
        {
            b=mid;
        }
        if(tmpmid<val)
        {
            a=mid;
        }
    }
    return(b+1);
}


template <class T>
void Vec<T>::merge(int l, int r, int m)
{
    int n1,n2,i,j,k;
    n1 = m - l + 1;
    n2 = r - m;
    Vec<T> L(n1), R(n2);
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
        if(L.get(i) < R.get(j))
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
    { //If Right Array R[] has more elements than Left Array L[]
        //then it will put all the
        // reamining elements of L[] into A[]
        set(k,R.get(j));
        k++;
        j++;
    }
}

template <class T>
void Vec<T>::mergesort(int l, int r)
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

template <class T>
void Vec<T>::sort()
{
    mergesort(0,current-1);
}

template class Vec<float>;



