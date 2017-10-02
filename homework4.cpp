#include <iostream>
#include <math.h>
using namespace std;
int Count=0;
int totalNum;
int map[100];
bool used[100];
void display(){
    for(int i=1;i<=totalNum;i++){
        for(int j=1;j<=totalNum;j++){
            if(map[i]==j){
                cout<<'X'<<' ';
            }
            else{
                cout<<'0'<<' ';
            }
        }
        cout<<endl;
    }
    cout<<endl;
}
bool Try(int x,int y){
    int j=1;
    while(j<x){
        if(map[j]==y||(abs(x-j)==abs(map[j]-y))){
            return false;
        }
        j++;
    }
    return true;
}
void dfs(int pos){
    if(pos>totalNum){
        Count++;
        display();
    }
    else{
        for(int i=1;i<=totalNum;i++){
            if(Try(pos,i)){
                map[pos]=i;
                dfs(pos+1);
            }
        }
    }
}
int main(void){
    bool check=false;
    cout<<"请输入皇后的个数:";
    do{
        cin>>totalNum;
        if(totalNum>0){
            check=true;
        }
    }while(!check);

    cout<<"皇后摆法:"<<endl;
    dfs(1);
    cout<<"共有"<<Count<<"🀄️种解法"<<endl;
}