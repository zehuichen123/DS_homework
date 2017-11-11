#include <iostream>
#include <algorithm>
using namespace std;
int wood[10000];            //用于保存所有的木头长度，默认最大值为10000
int main(void){
    int N;
    cout<<"please input N:";
    cin>>N;
    cout<<"please input the number of N woods:"<<endl;
    for(int i=0;i<N;i++){
        cin>>wood[i];
        if(wood[i]<=0){           //用于检测输入是否存在非法，若非法则重新输入该数据
            cout<<"the length of wood can not be negative!!"
                "please reinput this length:";
            i--;
            continue;
        }
    }
    long long answer=0;           //保存合成所有木块的花费总和
    sort(wood,wood+N);            //按照从小到大的顺序给数组排序
    for(int i=1;i<N;i++){
        wood[i]+=wood[i-1];       //每次取最小的两个木头进行合成
        answer+=wood[i];            
        for(int j=i;j<N-1;j++){   //去除之前的两个木头并将合成后的木头放入数组中
            if(wood[j]<wood[j+1]){
                swap(wood[j],wood[j+1]);
            }
            else{
                break;
            }
        }
    }
    cout<<answer<<endl;
}