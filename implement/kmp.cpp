#include <iostream>
using namespace std;
int Next[1000];
void getNext(string& b){
    int index=1,length=b.size();
    Next[0]=-1;
    while(index<length){
        if(b[index]==b[Next[index-1]]){
            Next[index]=Next[index-1]+1;
        }
        else{
            int temp=Next[index-1];
            while(temp>0){
                if(b[index]==b[Next[temp]]){
                    Next[index]=Next[temp]+1;
                    break;
                }
                else{
                    temp=Next[temp];
                }
            }
            if(temp==0&&b[index]==b[0]){
                Next[index]=1;
            }
        }
        index++;
    }
    for(int i=length-2;i>0;i--){
        Next[i+1]=Next[i];
    }
    return;
}
int main(void){
    string a,b;
    cin>>a>>b;				//a为母串，b为模式串
    int n=a.size(),m=b.size();
    getNext(b);
    for(int Count=0;Count<m;Count++){
        cout<<Next[Count]<<' ';
    }
    int i=0,j=0;			//i为a匹配到的位置，j为b匹配到的位置
    while(j<=m&&i<=n){
        if(a[i]==b[j]){
            i++;
            j++;
        }
        else{
            cout<<"shift"<<j-Next[j]<<endl;
            //i+=(j-Next[j]);
            j=Next[j];
        }
    }
    //最后根据i，j的值判断找到与否
}