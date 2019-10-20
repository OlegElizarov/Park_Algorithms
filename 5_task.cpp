#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;


template <class T>
class  Vector
{
public:

    typedef T * iterator;

    Vector();
    Vector(unsigned int size);
    Vector(unsigned int size, const T & initial);
    Vector(const Vector<T> & v);
    ~Vector();

    unsigned int capacity() const;
    unsigned int size() const;
    bool empty() const;
    iterator begin();
    iterator end();
    T & front();
    T & back();
    void push_back(const T & value);
    void pop_back();

    void reserve(unsigned int capacity);
    void resize(unsigned int size);

    T & operator[](unsigned int index);
    Vector<T> & operator=(const Vector<T> &);
    void clear();
private:
    unsigned int my_size;
    unsigned int my_capacity;
    T * buffer;
};

// Your code goes here ...
template<class T>
Vector<T>::Vector()
{
    my_capacity = 0;
    my_size = 0;
    buffer = 0;
}

template<class T>
Vector<T>::Vector(const Vector<T> & v)
{
    my_size = v.my_size;
    my_capacity = v.my_capacity;
    buffer = new T[my_size];
    for (unsigned int i = 0; i < my_size; i++)
        buffer[i] = v.buffer[i];
}

template<class T>
Vector<T>::Vector(unsigned int size)
{
    my_capacity = size;
    my_size = size;
    buffer = new T[size];
}

template<class T>
Vector<T>::Vector(unsigned int size, const T & initial)
{
    my_size = size;
    my_capacity = size;
    buffer = new T [size];
    for (unsigned int i = 0; i < size; i++)
        buffer[i] = initial;
    //T();
}

template<class T>
Vector<T> & Vector<T>::operator = (const Vector<T> & v)
{
    delete[ ] buffer;
    my_size = v.my_size;
    my_capacity = v.my_capacity;
    buffer = new T [my_size];
    for (unsigned int i = 0; i < my_size; i++)
        buffer[i] = v.buffer[i];
    return *this;
}

template<class T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return buffer;
}

template<class T>
typename Vector<T>::iterator Vector<T>::end()
{
    return buffer + size();
}

template<class T>
T& Vector<T>::front()
{
    return buffer[0];
}

template<class T>
T& Vector<T>::back()
{
    return buffer[my_size - 1];
}

template<class T>
void Vector<T>::push_back(const T & v)
{
    if (my_size >= my_capacity)
        reserve(my_capacity +5);
    buffer [my_size++] = v;
}

template<class T>
void Vector<T>::pop_back()
{
    my_size--;
}

template<class T>
void Vector<T>::reserve(unsigned int capacity)
{
    if(buffer == 0)
    {
        my_size = 0;
        my_capacity = 0;
    }
    T * Newbuffer = new T [capacity];
    //assert(Newbuffer);
    unsigned int l_Size = capacity < my_size ? capacity : my_size;
    //copy (buffer, buffer + l_Size, Newbuffer);

    for (unsigned int i = 0; i < l_Size; i++)
        Newbuffer[i] = buffer[i];

    my_capacity = capacity;
    delete[] buffer;
    buffer = Newbuffer;
}

template<class T>
unsigned int Vector<T>::size()const//
{
    return my_size;
}

template<class T>
void Vector<T>::resize(unsigned int size)
{
    reserve(size);
    my_size = size;
}

template<class T>
T& Vector<T>::operator[](unsigned int index)
{
    return buffer[index];
}

template<class T>
unsigned int Vector<T>::capacity()const
{
    return my_capacity;
}

template<class T>
Vector<T>::~Vector()
{
    delete[ ] buffer;
}
template <class T>
void Vector<T>::clear()
{
    my_capacity = 0;
    my_size = 0;
    buffer = 0;
}

typedef pair <int, int> Segment;

struct Compare{
    bool operator ()(const Segment a, const Segment b)
    {
        return a.first <= b.first;
    }
};



template <typename T,class Compare>
void merge(vector <T>& array, vector <T>& array1, vector <T>& array2,Compare cmp) {
    array.clear();

    int i, j, k;
    for( i = 0, j = 0, k = 0; i < array1.size() && j < array2.size(); k++){
        if(cmp(array1[i],array2[j])){
            array.push_back(array1[i]);
            i++;
        }else if(!cmp(array1[i],array2[j])){
            array.push_back(array2[j]);
            j++;
        }
        k++;
    }

    while(i < array1.size()){
        array.push_back(array1.at(i));
        i++;
    }

    while(j < array2.size()){
        array.push_back(array2[j]);
        j++;
    }
}

template <typename T,class Compare>
void merge_sort(vector <T>& array,Compare cmp) {
    if (1 < array.size()) {
        vector<T> array1(array.begin(), array.begin() + array.size() / 2);
        merge_sort(array1,cmp);
        vector<T> array2(array.begin() + array.size() / 2, array.end());
        merge_sort(array2,cmp);
        merge(array, array1, array2,cmp);
    }
}


int get_length(vector <Segment> segments) {
    int sum = 0;
    int l = -1;
    int r = 0;
    for (int i = 0; i < segments.size(); i++)
    {
        if (segments[i].first < r)
        {
            if (segments[i].second > r)
            {
                sum = sum + segments[i].second - r;}
        } else
            {
                sum = sum + segments[i].second - segments[i].first;
            }
            l = segments[i].first;
            if (segments[i].second > r)
            {
                r = segments[i].second;
            }
        }
        return sum;
}


int main()
{
    int size=0;
    int res=0;
    cin>>size;
    vector <Segment> vect(size);
    for (int i = 0; i <size ; ++i) {
        cin>>vect[i].first;
        cin>>vect[i].second;
    }

    merge_sort(vect,Compare());
    res=get_length(vect);


   /* for (int j = 0; j < size; ++j)
    {
        cout<<vect[j].first<<' '<<vect[j].second<<endl;
    }*/
    cout<< res;
    return 0;
}
