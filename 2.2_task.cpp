#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <typename T>
class Tree
{
    struct Node
    {
        Node(const T &value) : value(value), left(nullptr), right(nullptr) {}
        T value;
        Node *left;
        Node *right;

    };
public:
    Tree() : root(nullptr) {}
    ~Tree()
    {
        destroyTree(root);
    }
    void Add(const T &value)
    {
        root = addInternal(root, value);
    }
    void Print()
    {
        root = printer(root);
    }
private:
    Node* addInternal(Node *node, const T &value)
    {
        if (!node)
            return new Node(value);
        if (node->value <= value)
        {
            node->right = addInternal(node->right, value);
        }
        else
        {
            node->left = addInternal(node->left, value);
        }

        return node;
    }
    Node* printer(Node *node)
    {
        Node *temp=node;
        std::vector<Node*> visited;
        while (temp && std::find(visited.begin(),visited.end(),temp) == visited.end()) {

            // Visited left subtree
            if (temp->left &&
                    std::find(visited.begin(),visited.end(),temp->left) == visited.end())
                temp = temp->left;

                // Visited right subtree
            else if (temp->right &&
                    std::find(visited.begin(),visited.end(),temp->right) == visited.end())
                temp = temp->right;

                // Print node
            else {
                std::cout<<temp->value<<' ';
                visited.insert(visited.end(),temp);
                temp = node;
            }
        }



        /*if (node != nullptr)
        {
            node->left = printer(node->left,n);
            node->right = printer(node->right,n);
            std::cout<< node->value<<' ';
        }*/
        return nullptr;
    }
    void destroyTree(Node *node)
    {
        if (node)
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Node *root;
};

int main(int argc, const char * argv[]) {
    Tree<int> tree;
    int n=0;
    int value;
    std::cin>>n;
    for (int i = 0; i < n; i++)
    {
        std::cin>> value;
        tree.Add(value);
    }
    tree.Print();
    std::cin>>n;
    return 0;
}
