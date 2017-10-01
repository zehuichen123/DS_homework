#include<iostream>
using namespace std;
class Person{
public:
    Person(){}
    ~Person(){}

public:
    int number;
    Person* next;
    Person* former;
};
class People{
public:
    People();
    ~People(){};
    void Game();

public:
    int N;
    int S;
    int M;
    int K;
    Person* Head;
};
People::People() {
    cout<<"请输入生死游戏的总人数N:";
    cin>>N;
    cout<<"请输入游戏开始的位置S:";
    cin>>S;
    cout<<"请输入死亡数字M:";
    cin>>M;
    cout<<"请输入剩余的生者人数K:";
    cin>>K;
    auto ptr1=new Person;
    ptr1->number=1;
    Head=ptr1;
    for(int i=2;i<=N;i++){
        auto ptr2=new Person;
        ptr2->number=i;
        ptr2->former=ptr1;
        ptr1->next=ptr2;
        if(i==N){
            ptr2->next=Head;
            Head->former=ptr2;
        }
        ptr1=ptr2;
    }
}
void People::Game(){
    auto ptr=Head;
    for(int i=0;i<S-1;i++){
        ptr=ptr->next;
    }
    for(int i=1;i<=N-K;i++){
        for(int j=0;j<M-1;j++){
            ptr=ptr->next;
        }
        auto ptrFormer=ptr->former;
        auto ptrNext=ptr->next;
        ptrFormer->next=ptrNext;
        ptrNext->former=ptrFormer;
        cout<<"第"<<i<<"个死者的位置是："<<(ptr->number)<<endl;
        if(ptr==Head){
            Head=ptr->next;
        }
        delete(ptr);
        ptr=ptrNext;
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
}