#include <iostream>
using namespace std;

class Queue {
    int *data;
    int head;
    int tail;
    int dataSize;
    void growSize() {
        int newdataSize = (dataSize > 0) ? dataSize * 2 : 3,
                *newdata = new int[newdataSize];

        if(head != tail)
        {
            int j = 0;
            for(int i = head; i < tail; i++) {
                newdata[j++] = data[i];

                if(i == dataSize - 1)
                {
                    i = -1;
                }
            }
            head = 0;
            tail = j;
        }

        if(data != NULL) {
            delete[] data;
        }

        data = newdata;
        dataSize = newdataSize;
    }

public:
    Queue() {
        data = NULL;
        head = 0;
        tail = 0;
        dataSize = 0;
        growSize();
    }
    ~Queue() {
        if(data != NULL)
        {
            delete[] data;
        }
    }

    int pop()
    {
        if (head != tail)
        {
            int value=data[head];
            if (head+1==dataSize)
            {
             head=0;
            }
            else {
                head++;
            }

            return value;
        }
        return -1;
    }

    void push(int val) {

        if((tail + 1) % dataSize != head) {
            data[(tail) % dataSize] = val;
            tail = (tail + 1) % dataSize;
        }
        else
        {

            growSize();
            push(val);
            }
    }
    bool isEmpty() {
        return head == tail;
    }
};




int main() {
    Queue queue;
    int cmd_count = 0;
    cin >> cmd_count;

    int cmd_numb = 0,
    cmd_val = 0;

    bool checker = true;

    for(int i = 0; i < cmd_count; i++) {
        cin >> cmd_numb >> cmd_val;
        if(!checker) {
            continue;
        }
        switch(cmd_numb) {
            case 2:
                checker = (queue.pop() == cmd_val) && checker;
                break;
            case 3:
                queue.push(cmd_val);
                break;
            default:
                cout<<"error cmd";
                break;
        }
    }
    if (checker)
    {
        cout<<"YES";
    }
    else{
        cout << "NO";
    }

    return 0;
}