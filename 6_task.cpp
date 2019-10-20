#include <iostream>
using namespace std;

// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (int arr[], int low, int high)
{
    int ind=low+(rand()%(high-low));
    swap(arr[ind],arr[high]);

    int pivot = arr[high];
    // pivot
    int i = (high - 1);

    for (int j = high-1; j >= low; j--)
    {
        //if current element is smaller than pivot, increment the low element
        //swap elements at i and j
        if (arr[j] <= pivot)
        {
               // increment index of smaller element
            swap(&arr[i], &arr[j]);
            i--;
        }
    }
    swap(&arr[i +1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high,int *k)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);
        if (pi==*k)
        {
            *k=arr[pi];
        }
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1,&(*k));
        quickSort(arr, pi + 1, high,&(*k));
    }
}

/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Driver Code
int main()
{
    int size=0;
    cin>>size;
    int *arr =new int [size];
    int k=0;
    cin>>k;
    k=size-k-1;
    int bufk=k;
    for (int i = 0; i <size ; ++i) {
        cin>>arr[i];
    }
    quickSort(arr, 0, size - 1,&k);
    if (k==bufk)
    {
        k=arr[k];
    }
    cout<<k;
    return 0;
}