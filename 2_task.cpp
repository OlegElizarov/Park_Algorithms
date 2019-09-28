#include <iostream>

using namespace std;

int main() {
    int size1=0;
    int size2=0;
    cin >>size1>>size2;
    int *arr1=new int[size1];
    int *arr2=new int[size2];

    for (int i=0;i<size1;++i)
    {
        cin>>arr1[i];
    }

    for (int i=0;i<size2;++i)
    {
        cin>>arr2[i];
    }
    int x=0;
    int xmax=0;
    for (int i = 0; i <size2 ; ++i) {
        x=arr2[i];
        if (arr1[0]==x)
        {
            x=0;
            xmax=1;
            break;
        }
        for (int j=1;j<size1;j*=2)
        {
            if (j*2>size1)
            {
                if ((x>=arr1[j])&&(x<arr1[size1-1]))
                {
                    x=j;
                    xmax=size1-1;
                    break;}
            }

            if ((x>=arr1[j])&&(x<arr1[j*2]))
            {
                x=j;
                xmax=j*2;
                break;
            }
        }
    }
    cout<<x<<' '<<arr1[x]<<' '<<xmax<<' '<<arr1[xmax];

    return 0;
}