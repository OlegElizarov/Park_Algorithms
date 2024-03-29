#include <iostream>
#include <queue>

template<typename T>
class AvlTree {
    struct Node {
        Node(const T &value) : value(value), left(nullptr), right(nullptr), height(1) {}

        T value;
        Node *left;
        Node *right;
        unsigned char height;
    };

public:
    AvlTree() : root(nullptr) {}

    ~AvlTree() {
        destroyTree(root);
    }

    bool Has(const T &value) {
        Node *tmp = root;
        while (tmp) {
            if (tmp->value == value)
                return true;
            if (tmp->value < value)
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }
        return false;
    }

    T GetStat(int stat) {
        Node *tmp = Geter(root, stat);
        return tmp->value;
    }

    void Add(const T &value) {
        root = addInternal(root, value);
    }

    void Remove(const T &value) {
        root = removeInternal(root, value);
    }

private:

   int size(Node *node) {
        if (node == NULL)
            return 0;
        else
            if (node->left != nullptr && node->right != nullptr) {
                return (size(node->left) + 1 + size(node->right));
            }
            else if (node->left != nullptr)
            {
                return (size(node->left) + 1);
            }
            else if (node->right != nullptr) {
                return (size(node->right) + 1);
            } else return 1;
    }

    Node *Geter(Node *node, int stat) {
        if (size(node->left)  == stat || ( node->left == nullptr && node->right == nullptr ))
        {
            return node;
        } else if (size(node->left) > stat)
        {
            return Geter(node->left, stat);
        }
        else if (size(node->left) < stat) {
            return Geter(node->right, stat - size(node->left) - 1);
        }
    }

    Node *removeInternal(Node *node, const T &value) {
        if (!node)
            return nullptr;
        if (node->value < value) {
            node->right = removeInternal(node->right, value);
        } else if (node->value > value) {
            node->left = removeInternal(node->left, value);
        } else {
            Node *left = node->left;
            Node *right = node->right;

            delete node;

            if (!right)
                return left;

            Node *min;
            if (left == nullptr || (right->height > left->height)) {
                min = findMin(right);
                min->right = removeMin(right);
                min->left = left;
            } else {
                min = findMax(left);
                min->left = removeMax(left);
                min->right = right;

            }

            return doBalance(min);
        }

        return doBalance(node);
    }

    Node *findMin(Node *node) {
        while (node->left)
            node = node->left;
        return node;
    }

    Node *findMax(Node *node)
    {
        while (node->right)
            node = node->right;
        return node;
    }


    //need fix
    Node *removeMin(Node *node) {
        if (!node->left)
            return node->right;
        node->left = removeMin(node->left);
        return doBalance(node);
    }

    Node *removeMax(Node *node) {
        if (!node->right)
            return node->left;
        node->right = removeMax(node->right);
        return doBalance(node);
    }

    Node *addInternal(Node *node, const T &value) {
        if (!node)
            return new Node(value);
        if (node->value <= value) {
            node->right = addInternal(node->right, value);
        } else {
            node->left = addInternal(node->left, value);
        }

        return doBalance(node);
    }

    Node *doBalance(Node *node) {
        fixHeight(node);

        switch (getBalance(node)) {
            case 2: {
                if (getBalance(node->right) < 0)
                    node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            case -2: {
                if (getBalance(node->left) > 0)
                    node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            default:
                return node;
        }
    }

    int getBalance(Node *node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    void fixHeight(Node *node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    unsigned char getHeight(Node *node) {
        return node ? node->height : 0;
    }

    Node *rotateLeft(Node *node) {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;

        fixHeight(node);
        fixHeight(tmp);

        return tmp;
    }

    Node *rotateRight(Node *node) {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;

        fixHeight(node);
        fixHeight(tmp);

        return tmp;
    }

    void destroyTree(Node *node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Node *root;
};

int main(int argc, const char *argv[]) {
    AvlTree<int> avl;
    int value = 0;
    int stat = 0;
    size_t n = 0;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> value >> stat;
        if (value > 0) {
            avl.Add(value);
        } else {
            avl.Remove(-value);
        }
        std::cout << avl.GetStat(stat) << std::endl;
    }

    return 0;
}