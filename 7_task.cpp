#include<iostream>
#include <stdio.h>
#include <math.h>
using namespace std;



void LSD_sort(long long *arr, int n, int digit) {
    int *entries = new int[256]();

    for (int j = 0; j < n; j++) {
        long long digit_value = (arr[j] >> (8 * digit)) & 255;
        entries[digit_value]++;
    }

    for (int j = 1; j < 256; j++) {
        entries[j] += entries[j - 1];
    }

    auto temp = new long long[n];
    for (int j = n - 1; j >= 0; j--) {
        long long digit_value = (arr[j] >> (8 * digit)) & 255;
        temp[--entries[digit_value]] = arr[j];
    }

    memcpy(arr, temp, n * sizeof(long long));
    delete[] entries;
    delete[] temp;
}


long long find_max(long long arr[],int size)
{
    long long max_val=arr[0];
    for (int i = 1; i <size ; ++i) {
        if (arr[i]>max_val)
        {
            max_val=arr[i];
        }
    }
    return max_val;
}

void radixsort(long long arr[], int n)
{
    // Find the maximum number to know number of digits
    long long m = find_max(arr, n);
    int exp=0;
    exp=(int)log2(m)+1;
    exp/=8;
    for (int i = 0; i <=(exp) ; ++i)
    {
        LSD_sort(arr,n,i);
    }
  // for (int exp = 1; m/exp > 0; exp *= 10)
    //    countSort(arr,n,exp);
}

// A utility function to print an array
void print(long long arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}

// Driver program to test above functions
int main()
{
    int size=0;
    cin>>size;
    long long *arr=new long long[size];
    for (int i = 0; i <size ; ++i) {
        cin>>arr[i];
    }
    radixsort(arr, size);
    //LSD_sort(arr,size,0);
    print(arr, size);
    return 0;
}