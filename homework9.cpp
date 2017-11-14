#include <iostream>
using namespace std;
class Node{
public:
    Node():left(NULL),right(NULL){}         //初始化让左右两个节点为NULL
    ~Node(){}
    Node* left;                             //指向左子节点
    Node* right;                            //指向右子节点
    int value;                              //保存该节点的值
};
class bTree{                                //抽象整个二叉排序树
public:
    bTree(){}
    ~bTree(){}
    void Create();                          //构建二叉排序树
    Node* getHead(){return Head;}           //获得二叉排序树的头节点
    void setHead(Node* node){Head=node;}    //设置二叉排序树的头节点
    void Insert(int number);                //向树中插入新的元素
    bool Find(int number);                  //在二叉排序树中寻找是否有number元素
    void MidTraverse(Node* ptr);            //中序遍历二叉排序树
    void Display();                         //打印二叉排序树
private:
    Node* Head;                             //保存二叉排序树的头节点

};
void bTree::Create() {
    int num=1;
    cout<<"Please input key to create Bsort_Tree:"<<endl;
    do{
        cin>>num;
        if(num==0){                         //遇到输入为0停止输入
            break;
        }
        else{
            Insert(num);                    //将读入的数插入树中
        }
    }while(1);
    Display();                              //打印二叉排序树
}
void bTree::Display() {
    cout<<"Bsort_Tree is: "<<endl;
    auto head=getHead();
    MidTraverse(head);                      //调用中序遍历打印二叉排序树
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
    if(ptr){                                //如果二叉排序树当前不为空则向下查找可插入的位置
        while(1){
            if(number<ptr->value){          //如果插入的数比当前节点小就进入左子树
                if(ptr->left){
                    ptr=ptr->left;
                }
                else{                       //如果没有左子树就直接插入其左子树位置
                    ptr->left=node;
                    break;
                }
            }
            else if(number>ptr->value){     //如果插入的数比当前节点大就进入右子树
                if(ptr->right){
                    ptr=ptr->right;
                }
                else{                       //如果没有右子树就直接插入其右子树位置
                    ptr->right=node;
                    break;
                }
            }
            else{                           //如果插入的数已经存在树中则返回
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
    while(ptr){                             //寻找到ptr为NULL时返回未找到false
        if(ptr->value>number){
            ptr=ptr->left;
        }
        else if(ptr->value<number){
            ptr=ptr->right;
        }
        else{
            return true;                    //找到则直接返回true
        }
    }
    return false;
}
class System{                               //将整个程序操作抽象为系统
public:
    System();
    ~System(){}
    void Create();                          //构建二叉排序树
    void Insert();                          //插入操作
    void Find();                            //查找操作
    bTree bSortTree;                        //声明二叉排序树结构
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