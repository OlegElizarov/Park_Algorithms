#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


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
    DecTree() : root(nullptr) {}

    void setRoot(Node *_root) {
        root = _root;
    }

    void add(const T &data, int priority) {
        Node *node = new Node(data, priority),
                *curNode = root,
                *prevNode = root;

        if(curNode == NULL) {
            setRoot(node);
            return;
        }

        // Сначала спускаемся по дереву (как в обычном бинарном
        // дереве поиска по x), но останавливаемся на первом
        // элементе, в котором значение приоритета оказалось
        // меньше y.
        while(curNode != NULL && priority <= curNode->prior) {
            prevNode = curNode;
            if(data <= curNode->value) {
                curNode = curNode->left;
            }
            else
            {
                curNode = curNode->right;
            }
        }

        // Теперь разрезаем поддерево найденного элемента на T1 и
        // T2. Полученные T1 и T2 записываем в качестве левого и
        // правого сына добавляемого элемента.
        split(curNode, data, node->left, node->right);

        // Полученное дерево ставим на место элемента,
        // найденного в первом пункте.
        if(curNode == root) {
            root = node;
        }
        else if(data <= prevNode->value) {
            prevNode->left = node;
        }
        else
        {
            prevNode->right = node;
        }
    }

int treeHeight() {
        // Base Case
        if (root == NULL)
            return 0;

        // Create an empty queue for level order tarversal
        std::queue<Node *> q;

        // Enqueue Root and initialize height
        q.push(root);
        int height = 0;

        while (true) {
            // nodeCount (queue size) indicates number of nodes
            // at current lelvel.
            int nodeCount = q.size();
            if (nodeCount == 0)
                return height;

            height++;

            // Dequeue all nodes of current level and Enqueue all
            // nodes of next level
            while (nodeCount > 0) {
                Node *node = q.front();
                q.pop();
                if (node->left != NULL)
                    q.push(node->left);
                if (node->right != NULL)
                    q.push(node->right);
                nodeCount--;
            }
        }
    }

private:
Node *root;

Node *merge(Node *left, Node *right) {}

void split(Node *node, int key, Node *&left, Node *&right) {
    if (node == nullptr)
    {
        left = nullptr;
        right = nullptr;
    }
    else if (node->value <= key) {
        split(node->right, key, node->right, right);
        left = node;
    } else {
        split(node->left, key, left, node->left);
        right = node;
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

    int treeHeight() {
            // Base Case
            if (root == NULL)
                return 0;

            // Create an empty queue for level order tarversal
            std::queue<Node *> q;

            // Enqueue Root and initialize height
            q.push(root);
            int height = 0;

            while (true) {
                // nodeCount (queue size) indicates number of nodes
                // at current lelvel.
                int nodeCount = q.size();
                if (nodeCount == 0)
                    return height;

                height++;

                // Dequeue all nodes of current level and Enqueue all
                // nodes of next level
                while (nodeCount > 0) {
                    Node *node = q.front();
                    q.pop();
                    if (node->left != NULL)
                        q.push(node->left);
                    if (node->right != NULL)
                        q.push(node->right);
                    nodeCount--;
                }
            }
           }


    bool Add(const T &value) {
        if (root == nullptr) {
            root = new Node(value);
        }

        Node *current_node = root;
        while (true) {
            if (current_node->value == value) {
                return false;
            }

            if ((current_node->value < value)) {
                if (current_node->right == nullptr) {
                    current_node->right = new Node(value);
                }
                current_node = current_node->right;
            } else {
                if (current_node->left == nullptr) {
                    current_node->left = new Node(value);
                }
                current_node = current_node->left;
            }
        }
    }

    void Print() {
        printer(root);
    }

private:

    int maxDepth(Node* node)
    {
        if (node == NULL)
            return 0;
        else
        {
            /* compute the depth of each subtree */
            int lDepth = maxDepth(node->left);
            int rDepth = maxDepth(node->right);

            /* use the larger one */
            if (lDepth > rDepth)
                return(lDepth + 1);
            else return(rDepth + 1);
        }
    }



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

    Node *root;
};

typedef std::pair<int, int> Segment;

int find_max(std::vector<Segment> vector, int n) {
    int max = vector[0].second;
    int maxind = 0;
    for (int i = 1; i < n; ++i) {
        if (vector[i].second > max) {
            max = vector[i].second;
            maxind = i;
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

    for (int i = 0; i < n; i++) {
        std::cin >> value >> prior;
        tree.Add(value);
        dectree.add(value,prior);

    }
    std::cin >> n;
    //dectree.Print();
    std::cout << abs(dectree.treeHeight() - tree.treeHeight());
    return 0;
}