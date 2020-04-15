#ifndef VEC_H
#define VEC_H

template<class T>
class Vec
{
public:
    Vec();
    Vec(int index);
    Vec(const Vec & arg);
    Vec<T>& operator=(const Vec<T>& a);
    void print();
    int size() const;
    int begin() const;
    int end() const;
    T get(int index) const;
    void set(int index, T val);
    void insert(T val);
    void push_back(T data);
    int get_closest_value(T val) const;
    void merge(int a, int b, int c);
    void mergesort(int a, int b);
    void sort();
private:
    T* arr;
    int capacity;
    int current;
};

#endif // VEC_H
