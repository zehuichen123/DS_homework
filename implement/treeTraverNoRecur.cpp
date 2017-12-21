#include <iostream>
#include <stack>
using namespace std;
class Node{
public:
    Node():left(NULL),right(NULL),isVisited(false){}
    int value;
    Node* left;
    Node* right;
    bool isVisited;
};
class Tree{
public:
    Tree():Head(NULL){}
    ~Tree(){}
    void Insert(Node* node);
    Node* getHead();
    void setHead(Node* ptr);
private:
    Node* Head;
};
void Tree::Insert(Node* node) {
    if(Head){
        auto ptr=Head;
        while(1){
            if(node->value<=ptr->value){
                if(ptr->left){
                    ptr=ptr->left;
                }
                else{
                    ptr->left=node;
                    break;
                }
            }
            else{
                if(ptr->right){
                    ptr=ptr->right;
                }
                else{
                    ptr->right=node;
                    break;
                }
            }
        }
    }
    else{
        Head=node;
    }
}
Node* Tree::getHead() {
    return Head;
}
Tree tree;
void preTraverse2(Node* node){
    stack<Node*>temp;
    auto ptr=node;
    while(ptr||!temp.empty()){
        while(ptr){
            cout<<(ptr->value)<<' ';
            temp.push(ptr);
            ptr=ptr->left;
        }
        if(!temp.empty()){
            ptr=temp.top();
            temp.pop();
            ptr=ptr->right;
        }
    }
}
void midTraverse2(Node* node){
    stack<Node*>temp;
    auto ptr=node;
    while(ptr||!temp.empty()){
        while(ptr){
            temp.push(ptr);
            ptr=ptr->left;
        }
        if(!temp.empty()){
            ptr=temp.top();
            temp.pop();
            cout<<(ptr->value)<<' ';
            ptr=ptr->right;
        }
    }
}
void postTraverse2(Node* node){
    stack<Node*>temp;
    auto ptr=node;
    while(ptr||!temp.empty()){
        while(ptr){
            temp.push(ptr);
            ptr=ptr->left;
        }
        if(!temp.empty()){
            ptr=temp.top();
            if(!ptr->isVisited){
                ptr->isVisited=true;
                ptr=ptr->right;
            }
            else{
                cout<<(ptr->value)<<' ';
                temp.pop();
                ptr=NULL;
            }
        }
    }
}
void midTraverse(Node* node){
    if(node){
        midTraverse(node->left);
        cout<<(node->value)<<' ';
        midTraverse(node->right);
    }
}
void preTraverse(Node* node){
    if(node){
        cout<<(node->value)<<' ';
        preTraverse(node->left);
        preTraverse(node->right);
    }
}

void postTraverse(Node* node){
    if(node){
        postTraverse(node->left);
        postTraverse(node->right);
        cout<<node->value<<' ';
    }
}
int main(void){
    int num=1;
    while(1){
        cin>>num;
        if(num==-1){
            break;
        }
        auto ptr=new Node;
        ptr->value=num;
        tree.Insert(ptr);
    }
    /*preTraverse(tree.getHead());
    cout<<endl;
    preTraverse2(tree.getHead());
    midTraverse(tree.getHead());
    cout<<endl;
    midTraverse2(tree.getHead());
    postTraverse(tree.getHead());
    cout<<endl;
    postTraverse2(tree.getHead());*/
}