#include <iostream>
#include <vector>
using namespace std;
class person{
public:
    string name;
    vector<person*>children;
};
class multiTree{
public:
    multiTree();
    ~multiTree(){}
    void Create();
    void Add();
    void Delete();
    void Modify();
    void deleteChild(person* start);
    person* findName(person* ptr,string searchName);
    void Display(person* ptr);
private:
    person* head;
};
multiTree::multiTree() {
    cout<<"**                 家庭管理系统                   **"<<endl;
    cout<<"==================================================="<<endl;
    cout<<"**               请选择要执行的操作                **"<<endl;
    cout<<"**               A.---完善家谱                   **"<<endl;
    cout<<"**              B.---添加家庭成员                 **"<<endl;
    cout<<"**               C.---解散局部家庭                **"<<endl;
    cout<<"**               D.---更改家庭成员姓名             **"<<endl;
    cout<<"**               E.---退出程序                   **"<<endl;
    cout<<"=================================================="<<endl;
    cout<<"首先建立一个家谱"<<endl;
    cout<<"请输入祖先的姓名:";
    auto ptr=new person;
    cin>>ptr->name;
    cout<<"该家谱的祖先是:"<<ptr->name<<endl;
    head=ptr;
}
void multiTree::Display(person* ptr) {
    cout<<ptr->name<<"的第一代子孙是:";
    for(int i=0;i<ptr->children.size();i++){
        cout<<ptr->children[i]->name<<' ';
    }
    cout<<endl;
}
person* multiTree::findName(person* ptr,string searchName){
    if(ptr==NULL||ptr->name==searchName){
        return ptr;
    }
    else{
        for(int i=0;i<ptr->children.size();i++){
            auto tempPtr=findName(ptr->children[i],searchName);
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
    auto ptr=findName(head,searchName);
    if(ptr){
        int childNum;
        bool check=1;
        while(check){
            cout<<"请输入"<<searchName<<"的儿女人数:";
            cin>>childNum;
            if(childNum<0){
                cout<<"the number of children can not less than 0!"<<endl;
            }
            else{
                check=0;
            }
        }
        cout<<"请依次输入"<<searchName<<"的子女姓名:";
        getchar();
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
    else{
        cout<<"该家庭无此人!"<<endl;
        return;
    }
}
void multiTree::deleteChild(person *start) {
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
    auto ptr=findName(head,searchName);
    if(ptr){
        cout<<"要解散家庭的人是:"<<searchName<<endl;
        Display(ptr);
        deleteChild(ptr);
    }
    else{
        cout<<"该家庭无此人"<<endl;
    }
}
void multiTree::Modify(){
    cout<<"请输入要更改姓名的人目前姓名是:";
    string searchName;
    cin>>searchName;
    auto ptr=findName(head,searchName);
    if(ptr){
        cout<<"请输入修改后的姓名:";
        string tempName=ptr->name;
        cin>>ptr->name;
        cout<<tempName<<"已改名为"<<ptr->name<<endl;
    }
}
void multiTree::Add() {
    cout<<"请输入要添加儿子或女儿的姓名:";
    string searchName;
    cin>>searchName;
    auto ptr=findName(head,searchName);
    if(ptr){
        cout<<"请输入"<<searchName<<"要添加的儿子（或女儿）的姓名:";
        auto newChild=new person;
        cin>>(newChild->name);
        ptr->children.push_back(newChild);
        Display(ptr);
    }
    else{
        cout<<"该家庭无此人"<<endl;
        return;
    }
}
class System{
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
                break;
            }
            case 'B':{
                familyMap.Add();
                break;
            }
            case 'C':{
                familyMap.Delete();
                break;
            }
            case 'D':{
                familyMap.Modify();
                break;
            }
            case 'E':{
                return 0;
            }
            default:{
                cout<<"it seems that you didn't input a correct operand!"<<endl;
            }

        }
    }
}