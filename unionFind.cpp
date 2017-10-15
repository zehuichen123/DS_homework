#include <iostream>
#define Max 80
using namespace std;
int father[Max];
int rankArr[Max];
void makeSet(){
    for(int i=0;i<Max;i++){
        father[i]=i;                //首先每个节点的父节点都是本身
        rankArr[i]=0;               //每个树的初始高度都是0
    }
}
int findSet(int x){
    if(x!=father[x]){
        father[x]=findSet(father[x]);           //将每个寻找的子节点都直接指向最根节点
    }
    return father[x];
}
void unionSet(int x,int y){
    x=findSet(x);
    y=findSet(y);
    if(x==y){
        return;
    }
    else if(rankArr[y]<rankArr[x]){
        father[x]=y;
    }
    else if(rankArr[x]>rankArr[y]){
        father[y]=x;
    }
    else{
        father[x]=y;
        rankArr[y]++;
    }
}
int main(void){
    makeSet();
    father[1]=0;
    father[2]=1;
    father[3]=2;
    father[4]=3;
    findSet(4);
    for(int i=0;i<5;i++){
        cout<<i<<"'s father is "<<father[i]<<endl;
    }
    father[6]=5;
    father[7]=6;
    father[8]=7;
    findSet(8);
    for(int i=5;i<9;i++){
        cout<<i<<"'s father is "<<father[i]<<endl;
    }
    unionSet(3,7);
    for(int i=0;i<9;i++){
        cout<<i<<"'s father is "<<father[i]<<endl;
    }
}