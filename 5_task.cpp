#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;

typedef pair <int, int> Segment;

/*struct Compare{
    bool operator ()(const vector <Segment> a, const vector <Segment> b)
    {
        return a.second < b.second;
    }
};*/


template <  typename T,
        class Compare>
void mergeSort( vector<T> &arr, int start, int end, Compare comp)
{

    //if we're down to single elements, do nothing
    if ( start < end ){
        //call to right and left 'child'
        int mid = (start + end) / 2;

        mergeSort( arr, start, mid ,comp);
        mergeSort( arr, mid + 1, end ,comp);

        //call to merge
        merge( arr, start, mid, end);
    }
}




int get_length(vector <Segment> segments)
{
    int sum=0;
    for (int j=1;j<segments.size();j++) {
        for (int i = 0; i < segments.size()-j; i++) {
            if (segments[i].second > segments[i +1].second)
                swap(segments[i], segments[i +1]);
        }
    }
    int l=-1;
    int r=0;
    for (int i=0;i<segments.size();i++)
    {
     if (segments[i].first<r)
     {
         sum=sum+segments[i].second-r;
     } else
     {
         sum=sum+segments[i].second-segments[i].first;
     }
     l=segments[i].first;
     r=segments[i].second;
    }
    return sum ;
}


int main()
{
    int size=0;
    int res=0;
    cin>>size;
    vector <Segment> vect(size);
    for (int i = 0; i <size ; ++i) {
        cin>>vect[i].first>>vect[i].second;
    }

    mergeSort(vect,0,size-1,less<int >());
    //res=get_length(vect);


    for (int j = 0; j < size; ++j)
    {
        cout<<vect[j].first<<' '<<vect[j].second<<endl;
    }
    //cout<< res;
    return 0;
}
