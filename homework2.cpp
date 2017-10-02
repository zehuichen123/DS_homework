#include<iostream>
using namespace std;
class Person{
public:
    Person(){}
    ~Person(){}

public:
    int number;
    Person* next;
};
class People{
public:
    People();
    ~People(){};
    void Game();
    bool Check();

public:
    int N;
    int S;
    int M;
    int K;
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
    auto ptrFormer=Head;
    if(S==1){
        ptrFormer=Rear;
    }
    else{
        for(int i=0;i<S-2;i++){
            ptrFormer=ptrFormer->next;
        }
    }
    for(int i=0;i<S-1;i++){
        ptr=ptr->next;
    }
    for(int i=1;i<=N-K;i++){
        for(int j=0;j<M-1;j++){
            ptr=ptr->next;
            ptrFormer=ptrFormer->next;
        }
        auto ptrNext=ptr->next;
        ptrFormer->next=ptrNext;
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
    getchar();
}