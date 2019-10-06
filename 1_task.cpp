/*Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
 * Необходимо найти первую пару индексов i0 и j0, , такую что A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}.
 * Время работы - O(n). n ≤ 100000.
*/
#include <iostream>

using namespace std;

int main() {
    int size=0;
    cin >>size;
    int *arr1=new int[size];
    int *arr2=new int[size];

    for (int i=0;i<size;++i)
    {
        cin>>arr1[i];
    }

    for (int i=0;i<size;++i)
    {
        cin>>arr2[i];
    }

    int a=0;
    int b=0;
    int amax=0;

    for (int i=0;i<size;++i)
    {
        if (arr1[i]>arr1[amax])
        {
            amax=i;
        }
        if (arr1[amax]+arr2[i]>arr1[a]+arr2[b])
        {
            b=i;
            a=amax;
        }
    }

    cout<<a<<' '<<b<<endl;

    for (int i = 0; i <size ; ++i) {
        cout<<arr1[i]<<' ';
    }
    cout<<endl;
    for (int i = 0; i <size ; ++i) {
        cout<<arr2[i]<<' ';
    }
    delete[] arr1;
    delete[] arr2;
    return 0;
}