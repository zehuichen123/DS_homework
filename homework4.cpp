#include <iostream>
#include <math.h>
using namespace std;
int Count=0;                //n皇后问题解的个数
int totalNum;               //n的值（即皇后的个数）
int map[100];               //这里默认最大n为99，下标从1开始使用（即99*99）
void display(){             //展示可行解的摆放方式
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
bool Try(int x,int y){      //检查该摆放是否可行
    int j=1;
    while(j<x){             //可行条件为之前放入的行数和y不重复
                            //同时不能和之前放入的在对角线上
        if(map[j]==y||(abs(x-j)==abs(map[j]-y))){
            return false;
        }
        j++;
    }
    return true;
}

void dfs(int pos){          //深搜寻找解   
    if(pos>totalNum){       //当最后一列填完后就输出解
        Count++;
        display();
    }
    else{                   //从1-totalNum试可否放入第pos列第i行
        for(int i=1;i<=totalNum;i++){
            if(Try(pos,i)){        //如果可行就填入并进入下一个位置
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
    cout<<"共有"<<Count<<"种解法"<<endl;
}