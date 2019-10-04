#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int size=0;
    int data=0;
    cin>>size;
    vector<int> vec(size);
    for (int i = 0; i <size ; ++i) {
        cin>>data;
        vec[i]=data;
    }
    int sum=0;
    sort(vec.begin(),vec.end());

    while(vec.size()>2)
    {

        sum=sum+vec[0]+vec[1];
        vec[1]=vec[0]+vec[1];
        vec.erase(vec.begin());
        sort(vec.begin(),vec.end());
    }
    if (vec.size()==1)
    {
        sum=vec[0];
    }
    else
        sum=vec[0]+sum+vec[1];
    cout<<sum;
    /*for (int j = 0; j <size ; ++j) {
        cout<<vec[j]<<' ';
    }*/
    return 0;
}