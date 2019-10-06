#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;

typedef pair <int, int> Segment;

struct Compare{
    bool operator ()(const Segment a, const Segment b)
    {
        return a.first <= b.first;
    }
};



template <typename T,class Compare>
void merge(vector<T>& array, vector<T>& array1, vector<T>& array2,Compare cmp) {
    array.clear();

    int i, j, k;
    for( i = 0, j = 0, k = 0; i < array1.size() && j < array2.size(); k++){
        if(cmp(array1.at(i),array2.at(j))){
            array.push_back(array1.at(i));
            i++;
        }else if(!cmp(array1.at(i),array2.at(j))){
            array.push_back(array2.at(j));
            j++;
        }
        k++;
    }

    while(i < array1.size()){
        array.push_back(array1.at(i));
        i++;
    }

    while(j < array2.size()){
        array.push_back(array2.at(j));
        j++;
    }
}

template <typename T,class Compare>
void merge_sort(vector<T>& array,Compare cmp) {
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
