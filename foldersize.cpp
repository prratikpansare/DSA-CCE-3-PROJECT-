#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Node {
public:
    string name;
    int ownSize, totalSize;
    Node *left, *right;

    Node(string n, int s) {
        name = n;
        ownSize = totalSize = s;
        left = right = NULL;
    }
};

class FolderTree {
public:
    Node *root;

    FolderTree() {
        root = NULL;
    }

    Node* findFolder(string name) {
        if (!root) return NULL;
        stack<Node*> s;
        s.push(root);

        while (!s.empty()) {
            Node *t = s.top();
            s.pop();
            if (t->name == name) return t;
            if (t->right) s.push(t->right);
            if (t->left) s.push(t->left);
        }
        return NULL;
    }

    void createRoot() {
        if (root) {
            cout << "Root already exists!\n";
            return;
        }
        string name;
        int size;
        cout << "Root name and size (KB): ";
        cin >> name >> size;
        if (size < 0) {
            cout << "Invalid size!\n";
            return;
        }
        root = new Node(name, size);
        cout << "Root created!\n";
    }

    void addFolder() {
        if (!root) {
            cout << "Create root first!\n";
            return;
        }
        string parentName, name;
        int size;
        cout << "Parent folder: ";
        cin >> parentName;
        Node *p = findFolder(parentName);
        if (!p) {
            cout << "Parent not found!\n";
            return;
        }
        cout << "Subfolder name and size (KB): ";
        cin >> name >> size;
        if (size < 0 || findFolder(name)) {
            cout << "Invalid size or duplicate name!\n";
            return;
        }
        Node *n = new Node(name, size);
        if (!p->left) p->left = n;
        else if (!p->right) p->right = n;
        else {
            delete n;
            cout << "Maximum two subfolders allowed!\n";
            return;
        }
        cout << "Subfolder created!\n";
    }

    void display(Node *t) {
        if (!t) return;
        cout << t->name << " : " << t->ownSize << " KB\n";
        display(t->left);
        display(t->right);
    }

    void calculateSize() {
        if (!root) {
            cout << "Create root first!\n";
            return;
        }
        stack<Node*> s1, s2;
        s1.push(root);
        while (!s1.empty()) {
            Node *t = s1.top();
            s1.pop();
            s2.push(t);
            if (t->left) s1.push(t->left);
            if (t->right) s1.push(t->right);
        }
        cout << "\n--- Total Folder Sizes ---\n";
        while (!s2.empty()) {
            Node *t = s2.top();
            s2.pop();
            t->totalSize = t->ownSize;
            if (t->left) t->totalSize += t->left->totalSize;
            if (t->right) t->totalSize += t->right->totalSize;
            cout << t->name << " : " << t->totalSize << " KB\n";
        }
    }
};

int main() {
    FolderTree tree;
    int ch;
    do {
        cout << "\n1. Create Root\n2. Add Subfolder\n";
        cout << "3. Display Folders\n4. Calculate Sizes\n5. Exit\n";
        cout << "Choice: ";
        cin >> ch;
        switch (ch) {
        case 1: tree.createRoot(); break;
        case 2: tree.addFolder(); break;
        case 3:
            if (tree.root) tree.display(tree.root);
            else cout << "Create root first!\n";
            break;
        case 4: tree.calculateSize(); break;
        case 5: cout << "Program ended.\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (ch != 5);
    return 0;
}
