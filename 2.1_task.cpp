#include <iostream>
#include <vector>
#include <string.h>

const size_t DEFAULT_SIZE = 8;
const double MAX_ALPHA = 0.75;

size_t Hash(const std::string &s, size_t size, int step)
{
    size_t hash = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        hash = (hash * 71 + s[i]) % size;
    }
    if (step==0) {
        return hash;
    } else
    {
        //hash = (Hash(s,size,step-1)+ step+1) % size;
        hash=(hash+((step*step+step)/2))% size;
        return hash;
    }
}

template <typename T>
struct HashNode
{
    HashNode(const T &key, HashNode<T> *next) : key(key) {}
    T key;
    //bool status= false;//1-deleted;0-ok
};

template <typename T>
class HashTable
{
public:
    HashTable(size_t tableSize = DEFAULT_SIZE) : table(tableSize, nullptr) {}
    ~HashTable(){}

    bool Add(const T &key)
    {
        int step=0;
        if (size > table.capacity() * MAX_ALPHA)
        {
            grow();
        }
        int firstdelpos=-1;
        for( int i = 0; i < table.capacity(); ++i )
        {
            size_t hash = Hash(key, table.capacity(),step);
            HashNode<T> *node = table[hash];
            step++;
            if ( node != NULL && node->key[0] == 'D')
            {
                firstdelpos=hash;
            }
            if( node == NULL )
            {
                if (firstdelpos!= -1)
                {
                    table[firstdelpos] = new HashNode<T>(key, table[firstdelpos]);
                    size++;
                    return true;
                }
                table[hash] = new HashNode<T>(key, table[hash]);
                size++;
                step=0;
                return true;
            } else
            {
                if (node->key == key)
                {
                    return false;
                }
            }
        }

        step=0;
        return true;
        /*
        size_t hash = Hash(key, table.size(),step);

        HashNode<T> *node = table[hash];
        while (node != nullptr && node->key != key)
        {
            node = node->next;
        }

        if (node != nullptr)
            return false;

        table[hash] = new HashNode<T>(key, table[hash]);
        */
    }
    bool Delete(const T &key)
    {
        int step=0;
        while (step < table.capacity())
        {
            size_t hash = Hash(key, table.capacity(),step);
            HashNode<T> *node = table[hash];
            //step++;
            if ((node != NULL) && (node->key == key))
            {
                size--;
                node->key='D';
                return true;
            }
            if ((node != NULL) &&( node->key != key ))
            {
                step++;
            }
            if ((node == NULL))
            {
                step=0;
                return false;
            }
        }
        step=0;
        return false;        /*size_t hash = Hash(key, table.size(),step);

        HashNode<T> *prevNode = nullptr;
        HashNode<T> *node = table[hash];
        while (node != nullptr && node->key != key)
        {
            prevNode = node;
            node = node->next;
        }

        if (node == nullptr)
            return false;

        if (prevNode == nullptr)
        {
            table[hash] = node->next;
        }
        else
        {
            prevNode->next = node->next;
        }

        size--;
        delete node;
        return true;*/
    }

    bool Has(const T &key)
    {
        int step=0;
        while (step < table.capacity())
        {
            size_t hash = Hash(key, table.capacity(),step);
            HashNode<T> *node = table[hash];
            //step++;
            if ((node != NULL) && node->key == key)
            {
                return true;
            }
            if ((node != NULL) &&( node->key != key ))
            {
                step++;
            }
            if ((node == NULL))
            {
                step=0;
                return false;
            }
        }
        step=0;
        return false;
        /*
        size_t hash = Hash(key, table.size(),step);

        HashNode<T> *node = table[hash];
        while (node != nullptr && node->key != key)
        {
            node = node->next;
        }

        return node != nullptr;*/
    }
private:
    void grow()
    {
        std::vector<HashNode<T>*> newTable(table.capacity()*2, nullptr);

        for (size_t i = 0; i < table.capacity(); i++)
        {
            HashNode<T> *node = table[i];
            if (node == NULL)
            {
                continue;
            }
            int step=0;
            while (step<newTable.capacity())
            {

                size_t hash = Hash(node->key, newTable.capacity(),step);
                if (newTable[hash] == NULL)
                {
                    newTable[hash]=node;
                    break;
                }
                else{
                    step++;
                }
            }
        }
        table = std::move(newTable);
    }

    size_t size;
    std::vector<HashNode<T>*> table;
};

int main(int argc, const char * argv[]) {
    HashTable<std::string> table;

    char op='a';
    std::string key;
    while ((std::cin >> op >> key) && (op != '\0'))
    {

        switch (op)
        {
            case '?':
            {
                std::cout << (table.Has(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '+':
            {
                std::cout << (table.Add(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '-':
            {
                std::cout << (table.Delete(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            default:
                {
                    return 0;
                }
        }
    }
    return 0;
}
