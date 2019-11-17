#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <stdio.h>



template<typename T>
class DecTree {
    struct Node {
        Node(const T &value, const T &prior) : value(value), prior(prior), left(nullptr), right(nullptr) {}
        T value;
        T prior;
        Node *left;
        Node *right;
    };

public:
    DecTree(): root(nullptr){}

    void Print() {
        printer(root);
    }

    void Add(const T &value, const T &prior)
    {
        /*Node* left= new Node();
        Node* right= new Node();
        Node* node = new Node(value,prior);
        split(root,node->value,left,right);
        root=merge(merge(left,node),right);
        */

        if (root == NULL)
        {
            root = new Node(value,prior);
            return;
        }
        Node *tmp=root;
        Node *node = new Node(value,prior);
        Node *left= new Node(0,0);
        Node *right= new Node(0,0);
        while (tmp != NULL && tmp->prior > prior)
        {
            if (value>tmp->value)
            {
                if (tmp->right == NULL)
                {
                    tmp->right=new Node(node->value,node->prior);
                }
                tmp= tmp->right;
            } else
            {
                if (tmp->left == NULL)
                {
                    tmp->left=new Node(node->value,node->prior);
                }
                tmp = tmp->left;
            }
        }

        if (tmp != NULL)
        {
            split(tmp, tmp->value, left, right);
            node->left = left;
            node->right = right;
            tmp=node;
        }
    }

private:
    Node* root;
    Node* merge(Node* left, Node* right){}
    void split(Node* node,int key,Node*& left,Node*& right)
    {
        if( node == NULL ) {
            left = NULL;
            right = NULL;
        } else if( node->value <= key ) {
            split( node->right, key, node->right, right );
            left = node;
        } else {
            split( node->left, key, left, node->left );
            right = node;
        }
    }
    void printer(Node *node) {
        Node *temp = node;
        std::vector<Node *> visited;
        while (temp && std::find(visited.begin(), visited.end(), temp) == visited.end()) {

            // Visited left subtree
            if (temp->left &&
                std::find(visited.begin(), visited.end(), temp->left) == visited.end())
                temp = temp->left;

                // Visited right subtree
            else if (temp->right &&
                     std::find(visited.begin(), visited.end(), temp->right) == visited.end())
                temp = temp->right;

                // Print node
            else {
                std::cout << temp->value << ' ';
                visited.insert(visited.end(), temp);
                temp = node;
            }
        }

    }

};


template<typename T>
class Tree {
    struct Node {
        Node(const T &value) : value(value), left(nullptr), right(nullptr) {}

        T value;
        Node *left;
        Node *right;
    };

public:
    Tree() : root(nullptr) {}

    ~Tree() {
        //destroyTree(root);
        std::queue<Node *> queue;

        if (root != nullptr) {
            queue.push(root);
        }

        while (!queue.empty()) {
            Node *node = queue.front();
            queue.pop();

            if (node->left != nullptr) {
                queue.push(node->left);
                node->left = nullptr;
            }
            if (node->right != nullptr) {
                queue.push(node->right);
                node->right = nullptr;
            }

            if (node->left == nullptr && node->right == nullptr) {
                delete node;
            } else {
                queue.push(node);
            }
        }
    }

    void Add(const T &value) {
        root = addInternal(root, value);
    }

    void Print() {
        printer(root);
    }

private:
    Node *addInternal(Node *node, const T &value) {
        if (!node)
            return new Node(value);
        if (node->value <= value) {
            node->right = addInternal(node->right, value);
        } else {
            node->left = addInternal(node->left, value);
        }

        return node;
    }

    void printer(Node *node) {
        Node *temp = node;
        std::vector<Node *> visited;
        while (temp && std::find(visited.begin(), visited.end(), temp) == visited.end()) {

            // Visited left subtree
            if (temp->left &&
                std::find(visited.begin(), visited.end(), temp->left) == visited.end())
                temp = temp->left;

                // Visited right subtree
            else if (temp->right &&
                     std::find(visited.begin(), visited.end(), temp->right) == visited.end())
                temp = temp->right;

                // Print node
            else {
                std::cout << temp->value << ' ';
                visited.insert(visited.end(), temp);
                temp = node;
            }
        }

    }

    /*void destroyTree(Node *node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }*/

    Node *root;
};

typedef std::pair <int, int> Segment;

int find_max(std::vector<Segment> vector,int n)
{
    int max=vector[0].first;
    int maxind=0;
    for (int i = 1; i <n ; ++i) {
        if (vector[i].first>max)
        {
            max=vector[i].first;
            maxind=i;
        }
    }
    return maxind;
}

int main(int argc, const char *argv[]) {
    Tree<int> tree;
    DecTree<int> dectree;

    int n = 0;
    int value;
    int prior;
    std::cin >> n;
    std::vector<Segment > data(n);
    for (int i = 0; i < n; i++) {
        std::cin >> value >> prior;
        //tree.Add(value);
        data[i].first=value;
        data[i].second=prior;
    }
    int m=0;
    for (int i = 0; i < n; i++) {
        m=find_max(data,n);
        dectree.Add(data[m].first,data[m].second);
    }
    //tree.Print();
    return 0;
}
