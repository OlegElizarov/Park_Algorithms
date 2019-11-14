#include <iostream>
#include <vector>
#include <string.h>

template <typename T>
class AvlTree
{
    struct Node
    {
        Node(const T &value) : value(value), left(nullptr), right(nullptr) {}
        T value;
        Node *left;
        Node *right;

    };
public:
    AvlTree() : root(nullptr) {}
    ~AvlTree()
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
		if (node != nullptr)
		{
			node->right = printer(node->right);
			node->left = printer(node->left);
		std::cout<< node->value;
		}
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
    AvlTree<int> avl;
    int n=0;
    int value;
    std::cin>>n;
	for (int i = 0; i < n; i++)
	{
		std::cin>> value;
		 avl.Add(value);
	}
	avl.Print();
	std::cin>>n;
    return 0;
}

