#include <iostream>
#include <cstring>

struct Node
{
    int data;
    Node * left;
    Node * right;
};

class BST {
    private:
        Node * root;
        int size;
        
        void setSize();
        bool deleteTree(Node * node);
        bool insert(Node * current, Node * insertion);
    public:
        BST();
        BST(int data);

        ~BST();
        bool insert(int data);
        int getSize();
        Node * getRoot() {return root;}
        Node * search(Node * current, int data);
        bool deleteNode(Node * current, int data);
};

BST::BST() : root(nullptr), size(0)
{}

BST::BST(int data) 
{
    //Allocate our node
    Node * current = new Node;
    current->data = data;
    current->left = nullptr;
    current->right = nullptr;
    //update the size
    size = 1;
    //make the node our root
    this->root = current;
}

bool BST::deleteTree(Node * node)
{
    if(node != nullptr)
    {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
    }
    return true;
}

BST::~BST()
{
    deleteTree(root);  
}

bool BST::insert(Node * current, Node * insertion)
{
    bool success = false;
    if(insertion == nullptr)
        return false;
    if(insertion->data < current->data)
    {
        if(current->left == nullptr)
        {
            current->left = insertion;
            success = true;
        }
        else
        {
            success = insert(current->left, insertion);
        }
    }
    else if (insertion->data > current->data)
    {
        if(current->right == nullptr)
        {
            current->right = insertion;
            success = true;
        }
        else
        {
            success = insert(current->right, insertion);
        }
    }
    return success;
}

bool BST::insert(int data)
{
    bool success = false;
    Node * node = new Node;
    node->data = data;
    if(root == nullptr)
    {
        root = node;
        success = true;
    }
    else
    {
        success = insert(root, node);
    }

    return success;
}

Node * BST::search(Node * current, int data)
{
    Node * returnVal = nullptr;
    //base 
    if((current == nullptr) || current->data == data)
    {
        return current;
    }
    if(data > current->data)
    {
        returnVal = search(current->right, data);
    }
    if(data < current->data)
    {
        returnVal = search(current->left, data);
    }
    return returnVal;
}

void countdownIterative(int n)
{
    //print every number from n to 0
    do{
        std::cout << n << std::endl;
        //printf("%d\n",n);
        n--;
    }while(n >= 0);
}

void countdownRecursive(int n)
{
    printf("%d\n",n);
    // base case
    if(n > 0)
    {
        countdownRecursive(n-1);
    }
    return;
    // recursive case
}

bool BST::deleteNode(Node * current, int data)
{
    bool success = false;
    Node * temp = nullptr;
    if(current) //Base case. Yay!
    {
        if(current->right->data == data) //if data is on right
        {
            success = true;
            temp = current->right;
            if(current->right->left == nullptr && current->right->right == nullptr) //if data has no children
            {
                
                current->right = nullptr;
            }
            else if((current->right->right == nullptr) || !(current->right->left)) //if data has one child
            {
                if(current->right->right) //if child is on right
                {
                    current->right = current->right->right;

                }
                else
                {
                    current->right = current->right->left;
                }
            }
            else   //two children! 
            {
                Node * tempLeft = current->right->left;
                current->right = current->right->right;
                current->right->left = temp->left;
                insert(root, tempLeft);
                
            }
            delete temp;
        }
        else if(current->left->data == data) //if data is on left
        {
            success = true;
            temp = current->left;
            if(current->left->left == nullptr && current->left->right == nullptr) //if data has no children
            {
                
                current->left = nullptr;
            }
            else if((current->left->right == nullptr) || !(current->left->left)) //if data has one child
            {
                if(current->left->right) //if child is on right
                {
                    current->left = current->left->right;

                }
                else
                {
                    current->left = current->left->left;
                }
            }
            else   //two children! 
            {
                current->left = current->left->right;
                Node * tempLeft = current->left->left;
                current->left->left = temp->left;
                insert(root, tempLeft);
                
            }
            delete temp;
        }
        else if(data > current->data)
        {
            success = deleteNode(current->right, data);
        }
        else if(data < current->data)
        {
            success = deleteNode(current->left, data);
        }
        else if(data == current->data && current == root)
        {
            temp = root;
            Node * nodeLeft = current->left;
            root = root->right;
            insert(root, nodeLeft);
            delete temp;

        }
    }
    if(!current)
    {
        return false;
    }
    return success;
}

int main()
{
    countdownIterative(23);
    countdownRecursive(23);
    BST * bst = new BST;

    int entries[] = {50, 70, 30, 20, 40, 60, 80, 45, 55};
    for(int i = 0; i < 9; i++)
    {
        bst->insert(entries[i]);
    }
    Node * node = bst->getRoot();
    bst->search(node, 45);
    Node * val = bst->search(node, 56);
    if(val == nullptr)
        printf("No node found");
    bst->deleteNode(node, 70);
    bst->deleteNode(node, 50);
    node = bst->getRoot();
    bst->deleteNode(node, 45);
}