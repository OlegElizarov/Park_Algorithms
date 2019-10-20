#include<iostream>
using namespace std;

int find_max(long long arr[],int size)
{
    int max_val=arr[0];
    for (int i = 1; i <size ; ++i) {
        if (arr[i]>max_val)
        {
            max_val=arr[i];
        }
    }
    return max_val;
}
// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(long long arr[], int n, int exp)
{
    long long output[n]; // output array
    int i;
    int count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void LSD_sort(long long arr[],int size,int k)
{
    for (int l = 0; l <k ; ++l) {
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                int elem1=((arr[j] >> (8 * l)) & 255);
                int elem2=((arr[j+1] >> (8 * l)) & 255);
                if (elem1>elem2 ) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

void radixsort(long long arr[], int n)
{
    // Find the maximum number to know number of digits
    int m = find_max(arr, n);
    int exp=0;
    while (m>0)
    {
        m=m/2;
        exp++;
    }
    LSD_sort(arr,n,exp);
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