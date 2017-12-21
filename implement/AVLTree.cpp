#include <iostream>
using namespace std;
class Node{
public:
    Node():left(NULL),right(NULL){}
    ~Node(){}
    int value;
    Node* left;
    Node* right;
};
class AVLTree{
public:
    AVLTree():root(NULL){};
    ~AVLTree(){}
    Node* LLRota(Node* k2);
    Node* RRRota(Node* k2);
    Node* LRRota(Node* k3);
    Node* RLRota(Node* k3);
    Node* Insert(Node* root,int value);
    Node* Delete(Node* root,int value);
    int Height(Node* temp);
    int Diff(Node* temp);
    Node* Balance(Node* temp);
    Node* getRoot(){return root;}
    Node* getMax(Node* root);
    Node* getMin(Node* root);
    void setRoot(Node* temp){root=temp;}
    void display(Node* ptr,int level);
private:
    Node* root;
};
int AVLTree::Height(Node *temp) {
    int height=0;
    if(temp){
        int height_l=Height(temp->left);
        int height_r=Height(temp->right);
        height=max(height_l,height_r)+1;
    }
    return height;
}
int AVLTree::Diff(Node *temp) {
    int height_l=Height(temp->left);
    int height_r=Height(temp->right);
    return height_l-height_r;
}

Node* AVLTree::LLRota(Node* k2) {
    auto k1=k2->left;
    k2->left=k2->right;
    k1->right=k2;
    return k1;
}
Node* AVLTree::RRRota(Node *k2) {
    auto k1=k2->right;
    k2->right=k1->left;
    k1->left=k2;
    return k1;
}
Node* AVLTree::LRRota(Node *k3) {
    auto k1=k3->left;
    //auto k2=k1->right;
    k3->left=RRRota(k1);
    return LLRota(k3);
}
Node* AVLTree::RLRota(Node *k3) {
    auto k1=k3->right;
    //auto k2=k1->left;
    k3->right=LLRota(k1);
    return RRRota(k3);
}
Node* AVLTree::getMax(Node *root) {
    if(!root) {
        return NULL;
    }
    else{
        while(root->right){
            root=root->right;
        }
        return root;
    }
}
Node* AVLTree::getMin(Node* root){
    if(!root){
        return NULL;
    }
    else{
        while(root->left){
            root=root->left;
        }
        return root;
    }
}
Node* AVLTree::Balance(Node* temp){
    int bal_factor=Diff(temp);
    if(bal_factor>1){
        if(Diff(temp->left)>0){
            temp=LLRota(temp);
        }
        else{
            temp=LRRota(temp);
        }
    }
    else if(bal_factor<-1){
        if(Diff(temp->right)>0){
            temp=RLRota(temp);
        }
        else{
            temp=RRRota(temp);
        }
    }
    return temp;
}
Node* AVLTree::Insert(Node *root,int value) {
    if(!root){
        root=new Node;
        root->value=value;
    }
    else{
        if(root->value>value){
            root->left=Insert(root->left,value);
            root=Balance(root);
        }
        else{
            root->right=Insert(root->right,value);
            root=Balance(root);
        }
    }
    return root;
}
void AVLTree::display(Node *ptr, int level) {
    int i;
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1);
        printf("\n");
        if (ptr == getRoot())
            cout<<"Root -> ";
        for (i = 0; i < level && ptr != getRoot(); i++)
            cout<<"        ";
        cout<<ptr->value;
        display(ptr->left, level + 1);
    }
}
Node* AVLTree::Delete(Node *root, int value) {
    if(!root){
        return NULL;
    }
    else if(root->value>value){
        root->left=Delete(root->left,value);
        root=Balance(root);
    }
    else if(root->value<value){
        root->right=Delete(root->right,value);
        root=Balance(root);
    }
    else{
        if(root->right&&root->left){
            if(Diff(root)>0){
                auto biggest=getMax(root->left);
                root->value=biggest->value;
                root->left=Delete(root->left,biggest->value);
            }
            else{
                auto smallest=getMin(root->right);
                root->value=smallest->value;
                root->right=Delete(root->right,smallest->value);
            }
        }
        else{
            auto temp=root;
            root=root->right?root->right:root->left;
            delete(temp);
        }
    }
    return root;
}
int main(void){
    AVLTree myTree;
    while (1){
        cout<<"\n---------------------"<<endl;
        cout<<"AVL Tree Implementation"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Insert Element into the tree"<<endl;
        cout<<"2.Display Balanced AVL Tree"<<endl;
        //cout<<"3.InOrder traversal"<<endl;
        //cout<<"4.PreOrder traversal"<<endl;
        //cout<<"5.PostOrder traversal"<<endl;
        cout<<"7.Delete element in the tree"<<endl;
        cout<<"6.Exit"<<endl;
        cout<<"Enter your Choice: ";
        int choice;
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"Enter value to be inserted: ";
                int value;
                cin>>value;
                myTree.setRoot(myTree.Insert(myTree.getRoot(),value));
                break;
            case 2:
                if (myTree.getRoot() == NULL)
                {
                    cout<<"Tree is Empty"<<endl;
                    continue;
                }
                cout<<"Balanced AVL Tree:"<<endl;
                myTree.display(myTree.getRoot(), 1);
                break;
            /*case 3:
                cout<<"Inorder Traversal:"<<endl;
                avl.inorder(root);
                cout<<endl;
                break;
            case 4:
                cout<<"Preorder Traversal:"<<endl;
                avl.preorder(root);
                cout<<endl;
                break;
            case 5:
                cout<<"Postorder Traversal:"<<endl;
                avl.postorder(root);
                cout<<endl;
                break;*/
            case 7:{
                cout<<"input the number you want to delete:";
                int value;
                cin>>value;
                myTree.setRoot(myTree.Delete(myTree.getRoot(),value));
                break;
            }
            case 6:
                exit(1);
                break;
            default:
                cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
}

