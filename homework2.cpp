#include<iostream>
using namespace std;
class Person{                           
public:
    Person(){}
    ~Person(){}
public:
    int number;                         //每个人的序号
    Person* next;                       //指向下一个人
};
class People{                           
public:
    People();
    ~People(){};
    void Game();                        //开始进行模拟生死游戏
    bool Check();                       //检查初始输入是否合理

public:
    int N;                              //开始时参与该游戏总人数
    int S;                              //开始时从第S个人开始模拟
    int M;                              //每数到第M个人就让该人出列
    int K;                              //最后剩余K人时输出剩余人信息
    Person* Head;                       
    Person* Rear;
};
bool People::Check(){
    if(N<=0){
        cout<<"The total number N should be positive!"
                "Please REINPUT YOUR DATA!"<<endl;
        return false;
    }
    else if(S<=0){
        cout<<"The begin point S should be positive!"
                "Please REINPUT YOUR DATA!"<<endl;
        return false;
    }
    else if(M<=0){
        cout<<"The dead number M should be positive!"
                "Please REINPUT YOUR DATA!"<<endl;
        return false;
    }
    else if(K<=0){
        cout<<"The residual number K should be positive!"
                "Please REINPUT YOUR DATA!"<<endl;
        return false;
    }
    else if(S>N){
        cout<<"The begin point S should less than "
                "the total number N!"
                "Please REINPUT YOUR DATA!"<<endl;
        return false;
    }
    else if(K>N){
        cout<<"The residual number K must less than "
                "the total number N!"
                "Please REINPUT YOUR DATA!"<<endl;
        return false;
    }
    else{
        return true;
    }
}
People::People() {
    cout<<"现有N个人围成一圈，从第S个人开始依次报数，"
            "报M的人出局，再由下一个人开始报数。如此"
            "循环，直至只剩下K个人为止"<<endl;
    bool check;
    do{
        cout<<"请输入生死游戏的总人数N:";
        cin>>N;
        cout<<"请输入游戏开始的位置S:";
        cin>>S;
        cout<<"请输入死亡数字M:";
        cin>>M;
        cout<<"请输入剩余的生者人数K:";
        cin>>K;
        check=Check();
    }while(!check);
    /*构造一个循环单链表*/
    auto ptr1=new Person;
    ptr1->number=1;
    Head=ptr1;
    for(int i=2;i<=N;i++){
        auto ptr2=new Person;
        ptr2->number=i;
        ptr1->next=ptr2;
        if(i==N){
            ptr2->next=Head;
            Rear=ptr2;
        }
        ptr1=ptr2;
    }
}
void People::Game(){
    auto ptr=Head;
    auto ptrFormer=Head;            //指向当前位置的前一个人
    if(S==1){                       //如果当前初始位置为1，那么前一个人就是最后一个
        ptrFormer=Rear;
    }
    else{                           //如果不是就顺序遍历到第S-1位置
        for(int i=0;i<S-2;i++){
            ptrFormer=ptrFormer->next;
        }
    }
    for(int i=0;i<S-1;i++){         //将ptr指向初始位置也就是S位置
        ptr=ptr->next;
    }
    for(int i=1;i<=N-K;i++){        //进行N-K次模拟删除节点
        for(int j=0;j<M-1;j++){     //模拟数到第M个人(将ptr和ptrFormer一起迭代)
            ptr=ptr->next;
            ptrFormer=ptrFormer->next;
        }
        auto ptrNext=ptr->next;     //找到当前位置的下一个元素
        ptrFormer->next=ptrNext;    //将当前位置的前一个元素链接至当前位置的下一个元素
        cout<<"第"<<i<<"个死者的位置是："<<(ptr->number)<<endl;
        if(ptr==Head){              //如果当前位置为头节点就更新头节点的值（因为最后输出时要用到head）
            Head=ptr->next;
        }
        delete(ptr);                //删除该位置节点
        ptr=ptrNext;                //继续模拟操作
    }
    cout<<"最后剩下"<<K<<"人"<<endl;
    cout<<"剩余的生者位置为";
    auto alive=Head;
    for(int i=0;i<K;i++){
        cout<<alive->number<<"  ";
        alive=alive->next;
    }
    cout<<endl;
}
int main(void){
    People system1;
    system1.Game();
    cout<<"press any key to continue:";
    getchar();
    getchar();
}







