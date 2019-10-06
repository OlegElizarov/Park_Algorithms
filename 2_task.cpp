#include <iostream>

using namespace std;

void expan(int arr1[],int arr2[],int size1,int size2,int &x,int &xmax,int &val,int i) {
        val = arr2[i];
        if (arr1[0] >= val || (arr1[0] <= val && arr1[1] >= val)) {
            x = 0;
            xmax = 1;
        }
        if (xmax != 1) {
            for (int j = 1; j < size1; j *= 2) {
                if (j * 2 >= size1) {
                    if ((val >= arr1[j]) && (val <= arr1[size1 - 1])) {
                        x = j;
                        xmax = size1 - 1;
                        break;
                    }
                }

                if ((val >= arr1[j]) && (val < arr1[j * 2])) {
                    x = j;
                    xmax = j * 2;
                    break;
                }
            }
        }

}

int binarySearch(int arr[], int low, int high, int target)
{
    int mid;
    while (low < high)
    {
        mid = (low+high)/2;
        if (arr[mid] >= target)
            high = mid;
        else
            low = mid + 1;
    }

    if ( arr[low] >= target)
        return low;
    else
        return -1;
}

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
    int val=0;
    for (int i = 0; i <size2 ; ++i) {
        expan(arr1,arr2,size1,size2,x,xmax,val,i);
        x=binarySearch(arr1,x,xmax,val);
        if (x==-1)
        {
            cout<<size1<<' ';
        }
        else
        {cout<<x<<' ';}
        x=0;
        xmax=0;
    }
    return 0;
}