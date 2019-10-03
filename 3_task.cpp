#include <iostream>
using namespace std;

class Queue {
    int *data; // массив с числами
    int dataSize; // количество элементов, на которые выделена память

    int head; // номер первого элемента
    int tail; // номер последнего элемента

    // увеличивает кол-во памяти
    void growSize() {
        int newDataSize = (dataSize > 0) ? dataSize * 2 : 5, // размер новой памяти
                *newData = new int[newDataSize]; // новая память

        if(head != tail) {
            int j = 0; // временный индекс
            for(int i = head; i < dataSize; i++) {
                if(i == tail) { // элемент следующий после последнего
                    break;
                }

                newData[j++] = data[i];

                if(i == dataSize - 1) {
                    i = -1;
                }
            }
            head = 0;
            tail = j;
        }

        if(data != NULL) {
            delete[] data;
        }

        data = newData;
        dataSize = newDataSize;
    }

public:
    Queue() {
        data = NULL;
        dataSize = 0;

        head = 0;
        tail = 0;

        growSize();
    }

    ~Queue() {
        if(data != NULL) {
            delete[] data;
        }
    }

    // удаляет первый элемент и возвращает его
    int pop() {
        if(head != tail) {
            // очередь не пуста
            int val = data[head];

            if(head == dataSize - 1) {
                head = 0;
            }
            else
            {
                head++;
            }

            return val;
        }

        // очередь пуста
        return -1;
    }

    // добавляет новый элемент в конец
    void push(int val) {
        if((tail + 1) % dataSize == head) {
            // память закончилась
            growSize();
            push(val);
        }
        else
        {
            // добавляем следующий элемент
            data[(tail) % dataSize] = val;
            tail = (tail + 1) % dataSize;
        }
    }


    void show() {
        printf("[%d:%d:%d]==========\n", head, tail, dataSize);
        for (int i = head; i < dataSize; i++) {
            if (i == tail) { // элемент следующий после последнего
                break;
            }
            printf("[%d] => %d\n", i, data[i]);
            if (i == dataSize - 1) {
                i = -1;
            }
        }
        printf("/==========\n");
    }


    // очередь пуста?
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

    bool isOK = true;

    for(int i = 0; i < cmd_count; i++) {
        cin >> cmd_numb >> cmd_val;
        if(!isOK) {
            continue;
        }
        switch(cmd_numb) {
            case 2:
                /*if(queue.isEmpty()) {
                    cmd_val = -1;
                }*/
                isOK = (queue.pop() == cmd_val) && isOK;
                break;
            case 3:
                queue.push(cmd_val);
                break;
            default:
                cout<<"error cmd";
                break;
        }
    }
    queue.show();
    cout << (isOK ? "YES" : "NO");

    return 0;
}