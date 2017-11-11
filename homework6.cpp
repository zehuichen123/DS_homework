#include <iostream>
#include <vector>
using namespace std;
class person{                           //用于保存一个人的信息
public:
    string name;                        //该人姓名
    vector<person*>children;            //保存指向该人的孩子的指针
};
class multiTree{
public:
    multiTree();
    ~multiTree(){}
    void Create();                      //完善家谱
    void Add();                         //向家谱中添加孩子
    void Delete();                      //在家谱中解散成员
    void Modify();                      //修改家谱信息
    void deleteChild(person* start);    //在家谱中找到孩子并删除
    person* findName(person* ptr,string searchName);       //寻找姓名为searchName的孩子
    void Display(person* ptr);          //展示家谱
private:
    person* head;
};
multiTree::multiTree() {                    //构造家谱（即构造多叉树）
    cout<<"**                 家庭管理系统                   **"<<endl;
    cout<<"==================================================="<<endl;
    cout<<"**               请选择要执行的操作                **"<<endl;
    cout<<"**               A.---完善家谱                   **"<<endl;
    cout<<"**               B.---添加家庭成员                **"<<endl;
    cout<<"**               C.---解散局部家庭                **"<<endl;
    cout<<"**               D.---更改家庭成员姓名             **"<<endl;
    cout<<"**               E.---退出程序                   **"<<endl;
    cout<<"=================================================="<<endl;
    cout<<"首先建立一个家谱"<<endl;
    cout<<"请输入祖先的姓名:";                 //建立家谱祖先
    auto ptr=new person;
    cin>>ptr->name;
    cout<<"该家谱的祖先是:"<<ptr->name<<endl;
    head=ptr;
}
void multiTree::Display(person* ptr) {      //显示ptr指向的所有孩子姓名
    cout<<ptr->name<<"的第一代子孙是:";
    for(int i=0;i<ptr->children.size();i++){
        cout<<ptr->children[i]->name<<' ';
    }
    cout<<endl;
}
person* multiTree::findName(person* ptr,string searchName){
    if(ptr==NULL||ptr->name==searchName){   //如果找到或者找完就直接返回当前指针
        return ptr;
    }
    else{                                   //如果没有找到或者还可以继续向下查找
        for(int i=0;i<ptr->children.size();i++){
            auto tempPtr=findName(ptr->children[i],searchName);     //递归寻找
            if(tempPtr) {
                if (tempPtr->name == searchName) {
                    return tempPtr;
                }
            }
        }
    }
    return NULL;
}
void multiTree::Create() {
    cout<<"请输入要建立家庭的人的姓名;";
    string searchName;
    cin>>searchName;
    auto ptr=findName(head,searchName);     //寻找名字为searchName的家庭成员
    if(ptr){                                //如果找到该位家庭成员
        int childNum;
        bool check=1;
        while(check){
            cout<<"请输入"<<searchName<<"的儿女人数:";
            cin>>childNum;
            if(childNum<0){                 //检查输入是否合法
                cout<<"the number of children can not less than 0!"<<endl;
            }
            else{
                check=0;
            }
        }
        cout<<"请依次输入"<<searchName<<"的子女姓名:";
        getchar();                          //去除上次输入的'\n'
        //最后一次读入数据需要独立出来因为最后一个字符串末尾是'\n'而不是' '
        for(int i=0;i<childNum-1;i++){      
            auto childPtr=new person;
            getline(cin,childPtr->name,' ');
            (ptr->children).push_back(childPtr);
        }
        auto childPtr=new person;
        getline(cin,childPtr->name);
        (ptr->children).push_back(childPtr);
        Display(ptr);
    }
    else{                                   //如果没有找到该成员
        cout<<"该家庭无此人!"<<endl;
        return;
    }
}
void multiTree::deleteChild(person *start) {    //递归删除家庭成员从而删除其所有孩子节点
    if(start){
        return;
    }
    else{
        for(int i=0;i<start->children.size();i++){
            deleteChild(start->children[i]);
        }
        delete(start);
    }
}
void multiTree::Delete() {
    cout<<"请输入要解散家庭的人的姓名:";
    string searchName;
    cin>>searchName;
    auto ptr=findName(head,searchName);         //寻找名字为searchName的家庭成员
    if(ptr){                                    //如果找到该位家庭成员
        cout<<"要解散家庭的人是:"<<searchName<<endl;
        Display(ptr);
        deleteChild(ptr);                       //调用函数删除该家庭成员及其子节点
    }
    else{                                       //如果没有找到该位家庭成员
        cout<<"该家庭无此人"<<endl;
    }
}
void multiTree::Modify(){
    cout<<"请输入要更改姓名的人目前姓名是:";
    string searchName;
    cin>>searchName;
    auto ptr=findName(head,searchName);         //寻找名字为searchName的家庭成员
    if(ptr){                                    //如果找到该位家庭成员
        cout<<"请输入修改后的姓名:";
        string tempName=ptr->name;
        cin>>ptr->name;
        cout<<tempName<<"已改名为"<<ptr->name<<endl;
    }
    else{                                       //如果没有找到该位家庭成员
        cout<<"该家庭无此人"<<endl;
        return;
    }
}
void multiTree::Add() {
    cout<<"请输入要添加儿子或女儿的姓名:";
    string searchName;
    cin>>searchName;
    auto ptr=findName(head,searchName);         //寻找名字为searchName的家庭成员
    if(ptr){                                    //如果找到该位家庭成员
        cout<<"请输入"<<searchName<<"要添加的儿子（或女儿）的姓名:";
        auto newChild=new person;
        cin>>(newChild->name);
        ptr->children.push_back(newChild);
        Display(ptr);
    }
    else{                                       //如果没有找到该位家庭成员
        cout<<"该家庭无此人"<<endl;
        return;
    }
}
class System{                                   //将整个过程抽象为一个System
public:
    System();
    ~System(){};
    void Create();
    void Add();
    void Delete();
    void Modify();
private:
    multiTree familyTree;
};
System::System() {
}
void System::Create() {
    familyTree.Create();
}
void System::Delete() {
    familyTree.Delete();
}
void System::Add() {
    familyTree.Add();
}
void System::Modify() {
    familyTree.Modify();
}
int main(void){
    System familyMap;
    char operand='\0';
    while(operand!='E'){
        cout<<"请选择要执行的操作:";
        cin>>operand;
        switch (operand){
            case 'A':{
                familyMap.Create();
                cout<<"-----------"<<endl;
                break;
            }
            case 'B':{
                familyMap.Add();
                cout<<"-----------"<<endl;
                break;
            }
            case 'C':{
                familyMap.Delete();
                cout<<"-----------"<<endl;
                break;
            }
            case 'D':{
                familyMap.Modify();
                cout<<"-----------"<<endl;
                break;
            }
            case 'E':{
                return 0;
            }
            default:{
                cout<<"it seems that you didn't input a correct operand!"<<endl;
                cout<<"-----------"<<endl;
            }

        }
    }
}