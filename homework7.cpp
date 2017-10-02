#include <iostream>
#include <algorithm>
using namespace std;
int wood[10000];
int main(void){
    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>wood[i];
        if(wood[i]<=0){
            cout<<"the length of wood can not be negative!!"
                "please reinput this length:";
            i--;
            continue;
        }
    }
    long long answer=0;
    sort(wood,wood+N);
    for(int i=1;i<N;i++){
        wood[i]+=wood[i-1];
        answer+=wood[i];
        for(int j=i;j<N-1;j++){
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