#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <queue>
using namespace std;

struct BinaryNode {
    int key;
    BinaryNode* left = nullptr;
    BinaryNode* right = nullptr;
};

struct BinaryTree {
    BinaryNode* root = nullptr;

    void addNode(int key, BinaryNode* node) {
        if (!node) {
            this->root = new BinaryNode;
            root->key = key;
            cout << "The node was added as a root" << endl;
        }
        else if (key > node->key) {
            if (node->right == nullptr) {
                node->right = new BinaryNode;
                node->right->key = key;
                cout << "The node was added" << endl;
            }
            else {
                this->addNode(key, node->right);
            }
        }
        else {
            if (node->left == nullptr) {
                node->left = new BinaryNode;
                node->left->key = key;
                cout << "The node was added" << endl;
            }
            else {
                this->addNode(key, node->left);
            }
        }
    }

    BinaryNode* find(int key, BinaryNode* node) {
        if (!node) {
            cout << "Not found" << endl;
            return node;
        }

        if (node->key == key) {
            cout << "Node found" << endl;
            return node;
        }

        if (key > node->key)
            this->find(key, node->right);
        else
            this->find(key, node->left);
    }

    void deleteNode(int key, BinaryNode* node, BinaryNode* parent = nullptr) {
        if (!node) {
            cout << "Not found" << endl;
            return;
        }

        if (key > node->key)
            this->deleteNode(key, node->right, node);
        if (key < node->key)
            this->deleteNode(key, node->left, node);

        if (key == node->key) {
            if (node->left == nullptr && node->right == nullptr) {
                if (parent) {
                    if (parent->left && parent->left->key == key) {
                        if (parent->left->key == key) 
                            parent->left = nullptr;
                    }
                    if (parent->right) {
                        if (parent->right->key == key)
                            parent->right = nullptr;
                    }

                    delete node;
                }
                else {
                    delete root;
                    this->root = nullptr;
                }
            }
            else if (node->left && !node->right) {
                BinaryNode* temp = node->left;
                node->key = node->left->key;
                node->right = node->left->right;
                node->left = node->left->left;

                delete temp;
                temp = nullptr;
            }
            else if (!node->left && node->right) {
                BinaryNode* temp = node->right;
                node->key = node->right->key;
                node->left = node->right->left;
                node->right = node->right->right;

                delete temp;
                temp = nullptr;
            }
            else {
                if (!node->right->left) {
                    BinaryNode* temp = node->right;
                    node->key = node->right->key;
                    node->right = node->right->right;

                    delete temp;
                    temp = nullptr;
                }
                
                BinaryNode* temp = node->right;
                parent = node;
                while (temp->left) {
                    parent = temp;
                    temp = temp->left;
                }

                node->key = temp->key;

                this->deleteNode(temp->key, temp, parent);
            }
        }
    }

    void showTree(BinaryNode* node, int offset = 0) {
        if (node != nullptr) {
            cout << setw(offset) << " " << setw(0) << node->key << endl;
            showTree(node->left, offset + 2);
            showTree(node->right, offset + 2);
        }
    }

    double mid() {
        double sum = 0, count = 0;
        queue <BinaryNode*> nodes;
        BinaryNode* node;
        nodes.push(this->root);

        while (!nodes.empty()) {
            node = nodes.front();
            nodes.pop();

            sum += node->key;
            count++;

            if (node->left)
                nodes.push(node->left);
            if (node->right)
                nodes.push(node->right);
        }

        return sum / count;
    }

    int count() {
        int count = 0;
        queue <BinaryNode*> nodes;
        BinaryNode* node;
        nodes.push(this->root);

        while (!nodes.empty()) {
            node = nodes.front();
            nodes.pop();
            count++;

            if (node->left)
                nodes.push(node->left);
            if (node->right)
                nodes.push(node->right);
        }

        return count;
    }

    void deleteMax() {
        int mx = 0;
        queue <BinaryNode*> nodes;
        BinaryNode* node;
        nodes.push(this->root);

        while (!nodes.empty()) {
            node = nodes.front();
            nodes.pop();

            if (node->key > mx)
                mx = node->key;

            if (node->left)
                nodes.push(node->left);
            if (node->right)
                nodes.push(node->right);
        }

        this->deleteNode(mx, this->root);
    }
    
};

class TreeNode {
    vector<int> keys;
    int t;
    vector<TreeNode*> children;
    int n;
    bool leaf;

public:
    TreeNode(int t1, bool leaf1) {
        t = t1;
        leaf = leaf1;
        n = 0;
    }

    void splitNode(TreeNode* child) {
        TreeNode* newChild = new TreeNode(t, child->leaf);

        newChild->n = t - 1;
        child->n = t - 1;

        for (int i = 0; i < t - 1; i++) {
            newChild->keys.push_back(child->keys[t]);
            child->keys.erase(child->keys.begin() + t);
        }

        for (int i = 0; i < t; i++) {
            newChild->children.push_back(child->children[t]);
            child->children.erase(child->children.begin() + t);
        }
                                    
        int i = n - 1;
        children.push_back(NULL);
        keys.push_back(0);
        while (i >= 0 && keys[i] > child->keys.back()) {
            keys[i + 1] = keys[i];
            children[i + 1] = children[i];
            i--;
        }
        keys[i + 1] = child->keys.back();
        children[i + 2] = newChild;
        child->keys.erase(child->keys.begin() + child->keys.size() - 1);
        n++;

    }

    void insert(int k) {
        int i = n - 1;

        if (leaf) {
            children.push_back(NULL);
            keys.push_back(0);
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                children[i + 1] = children[i];
                i--;
            }
            keys[i + 1] = k;
            n++;
        }
        else {
            while (i >= 0 && keys[i] > k)
                i--;
            i++;

            if (children[i]->n == 2 * t - 1) {
                splitNode(children[i]);

                if (keys[i] < k)
                    i++;
            }

            children[i]->insert(k);
        }
    }

    void print(int level) {
        cout << setw(4 * level) << "";
        cout << "[";
        for (int i = 0; i < n; i++) {
            cout << keys[i];
            if (i < n - 1)
                cout << " ";
        }
        cout << "]" << endl;

        for (auto x : children)
            if (x)
                x->print(level + 1);
    }

    TreeNode* search(int k) {
        int i = 0;
        while (i < n && keys[i] < k)
            i++;

        if (i < n && keys[i] == k)
            return this;

        if (leaf)
            return NULL;

        return children[i]->search(k);
    }

    void deleteKey(int k) {
        for (int i = 0; i < n; i++)
            if (keys[i] == k) {
                if (leaf) {
                    keys.erase(keys.begin() + i);
                    children.erase(children.begin() + i);
                    n--;
                    return;
                }
                else {
                    if (children[i]->n >= t) {
                        int behinde = children[i]->keys[n - 1];
                        deleteKey(behinde);
                        keys[i] = behinde;
                    }
                    else if (children[i + 1]->n >= t) {
                        int after = children[i + 1]->keys[0];
                        deleteKey(after);
                        keys[i] = after;
                    }
                    else {
                        children[i]->keys.push_back(k);
                        for (int j = 0; j < children[i + 1]->n; j++) {
                            children[i]->keys.push_back(children[i + 1]->keys[j]);
                            children[i]->children.push_back(children[i + 1]->children[j]);
                            children[i]->n++;
                        }
                        children[i]->children.push_back(children[i + 1]->children.back());

                        delete children[i + 1];
                        children[i + 1] = NULL;
                        children[i]->deleteKey(k);
                    }
                    return;
                }
            }

        if (leaf)
            return;


        int i = 0;
        while (i < n && k > keys[i])
            i++;

        if (leaf)
            return;

        if (children[i]->n == t - 1) {
            if (children[i + 1] && children[i + 1]->n >= t) {
                children[i]->keys.push_back(keys[i]);
                children[i]->n++;
                keys[i] = children[i + 1]->keys[0];

                children[i]->children.push_back(children[i + 1]->children[0]);

                children[i + 1]->keys.erase(children[i + 1]->keys.begin() + 0);
                children[i + 1]->children.erase(children[i + 1]->children.begin() + 0);
                children[i + 1]->n--;
            }
            else if (children[i - 1] && children[i - 1]->n >= t) {
                children[i]->keys.insert(children[i]->keys.begin(), keys[i - 1]);
                keys[i - 1] = children[i - 1]->keys[children[i - 1]->n - 1];
                children[i]->n++;

                children[i]->children.insert(children[i]->children.begin(), children[i - 1]->children.back());

                children[i - 1]->keys.erase(children[i - 1]->keys.end() - 1);
                children[i - 1]->children.erase(children[i - 1]->children.end() - 1);
                children[i - 1]->n--;
            }
            else {
                if (children[i + 1]) {
                    children[i]->keys.push_back(keys[i]);
                    children[i]->n++;
                    for (int j = 0; j < children[i + 1]->n; j++) {
                        children[i]->keys.push_back(children[i + 1]->keys[j]);
                        children[i]->children.push_back(children[i + 1]->children[j]);
                        children[i]->n++;
                    }
                    children[i]->children.push_back(children[i + 1]->children.back());

                    keys.erase(keys.begin() + i);
                    delete children[i + 1];
                    children[i + 1] = NULL;
                }
                else {
                    children[i]->keys.insert(children[i]->keys.begin(), keys[i - 1]);
                    children[i]->n++;
                    for (int j = children[i - 1]->n - 1; j >= 0 ; j--) {
                        children[i]->keys.insert(children[i]->keys.begin(), children[i - 1]->keys[j]);
                        children[i]->children.insert(children[i]->children.begin(), children[i - 1]->children[j]);
                        children[i]->n++;
                    }
                    children[i]->children.insert(children[i]->children.begin(), children[i - 1]->children[0]);

                    keys.erase(keys.begin() + i);
                    delete children[i - 1];
                    children[i - 1] = NULL;
                }
            }
        }
        children[i]->deleteKey(k);
    }

    int getLevels() {
        if (leaf)
            return 1;
        else
            return 1 + children[0]->getLevels();
    }



    friend class BTree;
};

class BTree {
    TreeNode* root;
    int t;

public:
    BTree(int temp) {
        root = NULL;
        t = temp;
    }

    void insert(int k) {
        if (root == NULL) {
            root = new TreeNode(t, true);
            root->children.push_back(NULL);
            root->keys.push_back(k);
            root->children.push_back(NULL);
            root->n = 1;
        }
        else {
            if (root->n != 2 * t - 1)
                root->insert(k);
            else {
                TreeNode* newRoot = new TreeNode(t, false);


                newRoot->children.push_back(root);
                newRoot->splitNode(root);

                int i = 0;



                newRoot->insert(k);

                root = newRoot;
            }
        }
    }

    TreeNode* search(int k) {
        if (root)
            return root->search(k);
    }

    void print(int level = 0) {
        if (root != NULL)
            root->print(level);
    }

    void deleteKey(int k) {
        if (root)
            root->deleteKey(k);
    }

    int getLevels() {
        if (root)
            return root->getLevels();
    }

    TreeNode* getMax() {
        int mx = 0;
        TreeNode* maximum = NULL;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            if (current) {
                for (int key : current->keys)
                    if (key > mx) {
                        mx = key;
                        maximum = current;
                    }

                if (!current->leaf) {
                    for (TreeNode* child : current->children) {
                        q.push(child);
                    }
                }
            }
        }
        return maximum;
    }

    TreeNode* getMin() {
        int mn = 9999999999;
        TreeNode* minimum = NULL;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            if (current) {
                for (int key : current->keys)
                    if (key < mn) {
                        mn = key;
                        minimum = current;
                    }

                if (!current->leaf) {
                    for (TreeNode* child : current->children) {
                        q.push(child);
                    }
                }
            }
        }
        return minimum;
    }

    int getDif() {
        TreeNode* mn = getMin();
        TreeNode* mx = getMax();
        int mini = 9999999;
        int maxi = 0;
        
        for (int i = 0; i < mn->n; i++)
            if (mini > mn->keys[i])
                mini = mn->keys[i];

        for (int i = 0; i < mx->n; i++)
            if (maxi < mx->keys[i])
                maxi = mx->keys[i];


        return maxi - mini;
    }
};

int main() {
    BTree t(2);
    t.insert(4);
    t.insert(9);
    t.insert(15);
    t.insert(3);
    t.insert(5);
    t.insert(16);
    t.insert(14);
    t.insert(18);
    t.insert(20);
    t.insert(23);
    t.insert(1);
    t.insert(2);
    t.insert(6);
    t.insert(7);
    t.insert(24);
    t.insert(25);
    t.insert(26);
    t.insert(27);
    t.insert(28);
    t.insert(29);
    t.insert(30);
    t.insert(31);
    t.insert(32);
    t.insert(33);
    t.insert(34);
    t.insert(35);
    t.insert(36);
    t.insert(37);
    t.print();


    cout << endl << endl << endl << endl;
    cout << t.getDif();

}

