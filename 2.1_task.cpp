#include <iostream>
#include <vector>

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
        hash = (Hash(s,size,step-1)+ step) % size;
        return hash;
    }
}

template <typename T>
struct HashNode
{
    HashNode(const T &key, HashNode<T> *next) : key(key) {}
    T key;
    bool status= false;//1-deleted;0-ok
};

template <typename T>
class HashTable
{
public:
    HashTable(size_t tableSize = DEFAULT_SIZE) : table(tableSize, nullptr) {}
    ~HashTable()
    {
        for (size_t i = 0; i < table.size(); i++)
        {
            HashNode<T> *node = table[i];
            while (node != nullptr)
            {
                delete node;
            }
        }
    }

    bool Add(const T &key)
    {
        int step=0;
        if (size > table.size() * MAX_ALPHA)
        {
            grow();
        }

        for( int i = 0; i < table.size(); ++i )
        {
            size_t hash = Hash(key, table.size(),step);
            HashNode<T> *node = table[hash];
            step++;
            if( node == NULL )
            {

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
        return false;
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
        while (step < table.size())
        {
            size_t hash = Hash(key, table.size(),step);
            HashNode<T> *node = table[hash];
            //step++;
            if ((node != NULL) && node->key == key)
            {
                size--;
                node->key='0';
                node->status= true;
                return true;
            }
            if ((node != NULL) &&( node->key != key ))
            {
                step++;
            }
            if ((node != NULL)  && (node->status))
            {
                step=0;
                return false;
            }
            if ((node == NULL))
            {
                step++;
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
        while (step < table.size())
        {
            size_t hash = Hash(key, table.size(),step);
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
            if ((node != NULL)  && (node->status))
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
        std::vector<HashNode<T>*> newTable(table.size()*2, nullptr);

        for (size_t i = 0; i < table.size(); i++)
        {
            HashNode<T> *node = table[i];
            while (node != nullptr)
            {
                size_t newHash = Hash(node->key, newTable.size(),0);
                newTable[newHash] = node;
            }
        }

        table = std::move(newTable);
    }

    size_t size;
    std::vector<HashNode<T>*> table;
};

int main(int argc, const char * argv[]) {
    HashTable<std::string> table;

    char op;
    std::string key;

    while (std::cin >> op >> key)
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
                    std::cout<<"bad oper";
                    break;
                }
        }
    }
    return 0;
}
