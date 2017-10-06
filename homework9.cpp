#include <iostream>
using namespace std;
class Node{
public:
    Node():left(NULL),right(NULL){}
    ~Node(){}
    Node* left;
    Node* right;
    int value;
};
class bTree{
public:
    bTree(){}
    ~bTree(){}
    void Create();
    Node* getHead(){return Head;}
    void setHead(Node* node){Head=node;}
    void Insert(int number);
    bool Find(int number);
    void MidTraverse(Node* ptr);
    void Display();
private:
    Node* Head;

};
void bTree::Create() {
    int num=1;
    cout<<"Please input key to create Bsort_Tree:"<<endl;
    do{
        cin>>num;
        if(num==0){
            break;
        }
        else{
            Insert(num);
        }
    }while(1);
    Display();
}
void bTree::Display() {
    cout<<"Bsort_Tree is: "<<endl;
    auto head=getHead();
    MidTraverse(head);
    cout<<endl;
}
void bTree::MidTraverse(Node *ptr) {
    if(ptr){
        MidTraverse(ptr->left);
        cout<<ptr->value<<"->";
        MidTraverse(ptr->right);
    }
}
void bTree::Insert(int number){
    auto node=new Node;
    node->value=number;
    auto ptr=getHead();
    if(ptr){
        while(1){
            if(number<ptr->value){
                if(ptr->left){
                    ptr=ptr->left;
                }
                else{
                    ptr->left=node;
                    break;
                }
            }
            else if(number>ptr->value){
                if(ptr->right){
                    ptr=ptr->right;
                }
                else{
                    ptr->right=node;
                    break;
                }
            }
            else{
                cout<<"The input key<"<<number<<"> is have in!"<<endl;
                return;
            }
        }
    }
    else{
        setHead(node);
    }
}
bool bTree::Find(int number){
    auto ptr=getHead();
    while(ptr){
        if(ptr->value>number){
            ptr=ptr->left;
        }
        else if(ptr->value<number){
            ptr=ptr->right;
        }
        else{
            return true;
        }
    }
    return false;
}
class System{
public:
    System();
    ~System(){}
    void Create();
    void Insert();
    void Find();
    bTree bSortTree;
};
System::System() {
    cout<<"**                  二叉排序树                   **"<<endl;
    cout<<"=================================================="<<endl;
    cout<<"**               1.---建立二叉排序树              **"<<endl;
    cout<<"**               2.---插入元素                   **"<<endl;
    cout<<"**               3.---查询元素                   **"<<endl;
    cout<<"**               4.---退出程序                   **"<<endl;
    cout<<"=================================================="<<endl;
}
void System::Create() {
    bSortTree.Create();
}
void System::Insert() {
    int number;
    cout<<"Please input key which inserted: ";
    cin>>number;
    bSortTree.Insert(number);
    bSortTree.Display();
}
void System::Find() {
    int number;
    cout<<"Please input key which searched: ";
    cin>>number;
    if(bSortTree.Find(number)){
        cout<<"search success!"<<endl;
    }
    else{
        cout<<number<<" not existed!"<<endl;
    }
}
int main(void){
    System myTree;
    int operand;
    while(1){
        cout<<"Please select:  ";
        cin>>operand;
        switch(operand){
            case 1:{
                myTree.Create();
                break;
            }
            case 2:{
                myTree.Insert();
                break;
            }
            case 3:{
                myTree.Find();
                break;
            }
            case 4:{
                cout<<"press any key to continue"<<endl;
                getchar();
                getchar();
                return 0;
            }
            default:{
                cout<<"it seems your operand is not between 1-4"
                        "Please reinput your operand"<<endl;
            }
        }
    }
}