// 4_2. Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы двух
// чисел равно их сумме.
// Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от
// порядка вычислений.
// ((1+2)+3) -> 1+2 + 3+3 = 9
// ((1+3)+2) -> 1+3 + 4+2 = 10
// ((2+3)+1) -> 2+3 + 5+1 = 11
// Требуется написать программу, которая определяет минимальное время, достаточное для вычисления суммы
// заданного набора чисел.

#include <iostream>
#include <cassert>
#include <functional>

using namespace std;

template <class T> struct les {
    bool operator() (const T& x, const T& y) const {return x<y;}
    typedef T first_argument_type;
    typedef T second_argument_type;
    typedef bool result_type;
};


template <class T> struct greater {
    bool operator() (const T& x, const T& y) const {return x>y;}
    typedef T first_argument_type;
    typedef T second_argument_type;
    typedef bool result_type;
};

template <class T, class Comparator = les<T>>
class Heap {
public:
    Heap() : bufer(nullptr), buf_size(0), heap_size(0) {
        growSize();
    }
    Heap(const T *array, size_t size) : bufer(new T[size]), buf_size(size),
                                        heap_size(size) {
        for(int i = 0; i < size; i++) {
            bufer[i] = array[i];
        }
        build_heap();
    }
    ~Heap() {
        delete[] bufer;
    }

    void insert(T value) {
        if (buf_size == heap_size) {
            growSize();
        }

        heap_size++;
        bufer[heap_size - 1] = value;
        sift_up(heap_size - 1);
    }
    T extract_min() {
        assert(heap_size != 0);

        T value = bufer[0];
        bufer[0] = bufer[--heap_size];
        if (heap_size != 0) {
            sift_down(0);
        }

        return value;
    }
    bool is_empty() const {
        return heap_size == 0;
    }

private:
    T *bufer;
    size_t buf_size;
    size_t heap_size;
    Comparator cmp = Comparator();

    void growSize() {
        T *old_buf = bufer;

        buf_size *= 2;
        bufer = new T[buf_size];
        for (size_t i = 0; i < heap_size; i++) {
            bufer[i] = old_buf[i];
        }

        delete[] old_buf;
    }

    void sift_down(size_t i) {
        size_t left = i * 2 + 1;
        size_t right = i * 2 + 2;

        size_t i_min = i;

        if (left < heap_size && cmp(bufer[left], bufer[i])) {
            i_min = left;
        }
        if (right < heap_size && cmp(bufer[right], bufer[i_min])) {
            i_min = right;
        }

        if (i_min != i) {
            swap(bufer[i_min], bufer[i]);
            sift_down(i_min);
        }
    }
    void sift_up(size_t i) {
        if (i == 0) {
            return;
        }

        size_t parent = (i - 1) / 2;
        if (bufer[i] < bufer[parent]) {
            swap(bufer[i], bufer[parent]);
            sift_up(parent);
        }
    }
    void build_heap() {
        for (size_t i = heap_size / 2 - 1; i > 0; i--) {
            sift_down(i);
        }
        sift_down(0);
    }
};

/*
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

    return 0;
}
*/


int main() {
    int size = 0;
    cin >> size;
    assert(size>0);
    int *vect = new int[size];
    for (size_t i = 0; i < size; i++) {
        cin >> vect[i];
    }

    Heap <int> heap(vect, size_t(size));

    int elem1=0,elem2=0;
    size_t sum = 0;
    while (!heap.is_empty()) {
        elem1 = heap.extract_min();

        if (heap.is_empty())
        {
            cout << sum;
        }
        else
        {
            elem2 = heap.extract_min();
            sum += elem2 + elem1;
            heap.insert(elem1 + elem2);
        }
    }

    delete[] vect;

    return 0;
}