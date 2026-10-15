#include <iostream>
#include <stack>
using namespace std;

class Node {
public:
    string name;
    int size;
    Node *left, *right;

    Node(string n, int s) {
        name = n;
        size = s;
        left = right = NULL;
    }
};

class FolderTree {
public:
    Node *root;

    FolderTree() {
        root = NULL;
    }

    void createFolders() {
        root = new Node("MainFolder", 10);

        root->left = new Node("Documents", 20);
        root->right = new Node("Pictures", 30);

        root->left->left = new Node("Notes", 5);
        root->left->right = new Node("Projects", 15);

        root->right->left = new Node("Photos", 25);
        root->right->right = new Node("Videos", 40);
    }

    void displayFolders(Node *temp) {
        if (temp == NULL)
            return;

        cout << "Folder: " << temp->name
             << " | Size: " << temp->size << " KB" << endl;

        displayFolders(temp->left);
        displayFolders(temp->right);
    }

    void calculateSize() {
        if (root == NULL) {
            cout << "No folders available!\n";
            return;
        }

        stack<Node*> s1, s2;
        s1.push(root);

        while (!s1.empty()) {
            Node *temp = s1.top();
            s1.pop();

            s2.push(temp);

            if (temp->left != NULL)
                s1.push(temp->left);

            if (temp->right != NULL)
                s1.push(temp->right);
        }

        cout << "\n--- Total Folder Sizes ---\n";

        while (!s2.empty()) {
            Node *temp = s2.top();
            s2.pop();

            if (temp->left != NULL)
                temp->size += temp->left->size;

            if (temp->right != NULL)
                temp->size += temp->right->size;

            cout << temp->name << " : "
                 << temp->size << " KB" << endl;
        }
    }
};

int main() {
    FolderTree tree;
    int choice;

    do {
        cout << "\n===== FOLDER SIZE CALCULATOR =====\n";
        cout << "1. Create Folder Structure\n";
        cout << "2. Display Folders\n";
        cout << "3. Calculate Folder Sizes\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            tree.createFolders();
            cout << "Folder structure created!\n";
            break;

        case 2:
            if (tree.root == NULL)
                cout << "Create folders first!\n";
            else
                tree.displayFolders(tree.root);
            break;

        case 3:
            tree.calculateSize();
            break;

        case 4:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}
