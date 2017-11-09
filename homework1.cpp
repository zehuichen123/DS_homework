#include <iostream>
using namespace std;
int stuNum;
class Stu{
public:
    Stu();
    ~Stu(){};
public:
    string number;                      //考生学号
    string name;                        //考生姓名
    string sex;                         //性别
    int age;                            //年龄
    string catagery;                    //职业
    Stu* next;                          //指向下一个考生
    Stu* former;                        //指向前一个考生
};
Stu::Stu():next(NULL),former(NULL){
}

class System{
public:
    System();
    ~System();
    void Display();                     //显示所有考生信息
    void Insert();                      //插入考生信息
    void Find();                        //查找考生是否存在
    void Modify();                      //修改考生信息
    Stu* FindByOrder(int Pos);          //按照考生顺序寻找考生
    Stu* FindByNum(string stuNumber);   //按照考生学号寻找考生
    void Del();                         //删除考生  
    void getInfo(Stu* obj);             //获得考生信息
private:
    int stuNum;
    Stu* Head;
};
void System::getInfo(Stu* obj){
    getline(cin,obj->number,' ');
    getline(cin,obj->name,' ');
    getline(cin,obj->sex,' ');
    cin>>(obj->age);
    getchar();
    getline(cin,obj->catagery);
}
System::System() {
    cout<<"首先请建立考生信息系统"<<endl;
    while(1){
        cout<<"请输入考生人数：";
        cin>>stuNum;
        getchar();
        if(stuNum<0){
            cout<<"student number must > 0"<<endl;
            continue;
        }
        else if(stuNum>0){
            cout<<"请一次输入考生的考号，姓名，性别，年龄及报考类别！"<<endl;
            Stu *ptr1,*ptr2;
            ptr1=new Stu;
            Head=ptr1;
            getInfo(ptr1);                          //从stdin读入一位考生信息
            for(int i=0;i<stuNum-1;i++){            //读入剩下stuNum-1位考生信息
                ptr2=new Stu;
                getInfo(ptr2);
                ptr1->next=ptr2;                    
                ptr2->former=ptr1;
                ptr1=ptr2;
            }
        }
        break;
    }
    Display();
}
System::~System() {
    auto ptr=Head;
    for(int i=0;i<stuNum;i++){
        ptr=Head->next;
        delete(ptr->former);
    }
    stuNum=0;
    ptr=Head=NULL;
}
void System::Display(){
    cout<<"考号     姓名     性别     年龄    报考类别"<<endl;
    auto ptr=Head;
    for(int i=0;i<stuNum;i++){
        cout<<ptr->number<<"      "<<ptr->name<<"      "
            <<ptr->sex<<"      "<<ptr->age<<"      "
            <<ptr->catagery<<endl;
        ptr=ptr->next;
    }
}
Stu* System::FindByOrder(int Pos) {
    if(Pos>stuNum||Pos<=0){                 //当找不到时返回NULL
        return NULL;
    }
    auto ptr=Head;
    Pos--;
    while(Pos--){                           //找到第pos位考生并返回指向
        ptr=ptr->next;                      //该位考生的指针
    }
    return ptr;
}
Stu* System::FindByNum(string stuNumber) {
    auto ptr=Head;
    int count=stuNum;
    while(count--){
        //cout<<stuNumber<<endl;
        if(ptr->number==stuNumber){
            return ptr;                     //如果找到该位考生返回指向他的指针
        }
        else{
            ptr=ptr->next;
        }
    }
    return NULL;                            //如果没有找到则返回NULL
}
void System::Insert() {
    int Pos;
    while(1){
        cout<<"请输入你要插入的位置：";
        cin>>Pos;
        getchar();
        if(Pos<=0||Pos>stuNum+1){           //如果插入的位置不存在就报错重新输入
            cerr<<"can not insert at"<<Pos<<endl;
            continue;
        }
        else{
            cout<<"请依次输入要插入的考生的考号，性别，年龄及报考类别:"<<endl;
            auto ptr1=new Stu;
            getInfo(ptr1);
            if(Pos==1){                     //插入的位置在首位
                if(stuNum){
                    Head->former=ptr1;
                    ptr1->next=Head;
                    Head=ptr1;
                }
                else{
                    Head=ptr1;
                }
            }
            else if(Pos==stuNum+1){         //插入的位置在末尾
                auto position=FindByOrder(stuNum);
                position->next=ptr1;
                ptr1->former=position;
            }
            else{                           //插入的位置在中间
                auto position=FindByOrder(Pos);
                auto temp=position->former;
                temp->next=ptr1;
                ptr1->former=temp;
                position->former=ptr1;
                ptr1->next=position;
            }
            stuNum++;
        }
        break;
    }
    Display();
    return;
}

void System::Del() {
    string stuNumber;
    cout<<"请输入要删除的考生的考号: ";
    cin>>stuNumber;
    auto position=FindByNum(stuNumber);     //寻找该位置的考生
    if(position){                           //如果找到该位考生就执行删除操作
        cout<<"你要删除的考生信息是：";
        cout<<position->number<<"      "<<position->name<<"      "
            <<position->sex<<"      "<<position->age<<"      "
            <<position->catagery<<endl;
        if(position==Head){                 //如果删除的考生在首位
            auto posNext=position->next;
            posNext->former=NULL;
            Head=posNext;
            delete position;
        }
        else{                               //如果删除的考生不在首位
            auto posFormer=position->former;
            auto posNext=position->next;
            if(posNext){
                posFormer->next=posNext;
                posNext->former=posFormer;
            }
            else{
                posFormer->next=NULL;
            }
        }
        stuNum--;
    }
    else{
        cerr<<"can not find this student"<<endl;
    }
    Display();                              //显示删除后所有考生信息
    return;
}
void System::Find(){
    string stuNumber;
    cout<<"请输入要查找的考生考号"<<endl;
    cin>>stuNumber;
    auto position=FindByNum(stuNumber);
    if(position){
        cout<<"考号     姓名     性别     年龄    报考类别"<<endl;
        cout<<position->number<<"      "<<position->name<<"      "
            <<position->sex<<"      "<<position->age<<"      "
            <<position->catagery<<endl;
    }
    else{
        cerr<<"can not find this student"<<endl;
    }
    return;
}
void System::Modify() {
    string stuNumber;
    cout<<"请输入你要修改的考生考号:";
    cin>>stuNumber;
    getchar();
    auto position=FindByNum(stuNumber);
    if(position){
        cout<<"请依次输入要插入的考生的考号，性别，年龄及报考类别:";
        getInfo(position);
    }
    else{
        cerr<<"can not find this student"<<endl;
    }
    return;
}
int main(void)
{
    System system1;
    int operand;
    do{
        cout<<"请选择您要进行的操作（1为插入，2为删除，"
                "3为查找，4为修改，5为统计，0为取消操作"<<endl;
        cout<<"请选择您要的操作：";
        cin>>operand;
        getchar();
        switch(operand){
            case 1:{
                system1.Insert();
                break;
            }
            case 2:{
                system1.Del();
                break;
            }
            case 3:{
                system1.Find();
                break;
            }
            case 4:{
                system1.Modify();
            }
            case 5:{
                system1.Display();
                break;
            }
            case 0:{
                break;
            }
            default:{
                cout<<"it seems that you didn't"
                "input a number between 0-5"<<endl;
            }
        }
    }while(operand);
}
