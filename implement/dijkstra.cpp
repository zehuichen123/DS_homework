/*
0 1 12 0 0 0
0 0 9 3 0 0
0 0 0 0 5 0
0 0 4 0 13 15
0 0 0 0 0 4
0 0 0 0 0 0
 */

#include <iostream>
#include <vector>
#define SIZE 15
#define INF 0x6fffffff
using namespace std;
int vertexNum;
int map[SIZE][SIZE];
int dis[SIZE];
int used[SIZE];
void getEdge(){
    cout<<"the number of vertexes:"<<endl;
    cin>>vertexNum;
    cout<<"input the adjecent matrix:"<<endl;
    for(int i=0;i<vertexNum;i++){
        for(int j=0;j<vertexNum;j++){
            cin>>map[i][j];
            if(map[i][j]==0){
                map[i][j]=INF;
            }
        }
    }
}
void dijkstra(int start){
    used[start]=true;
    for(int i=0;i<vertexNum;i++){
        dis[i]=map[start][i];
    }
    int Count=0;
    while(Count!=vertexNum-1){
        int temp,minDis=INF;
        for(int i=0;i<vertexNum;i++){
            if(dis[i]<minDis&&!used[i]){
                temp=i;
                minDis=dis[i];
            }
        }
        used[temp]=true;
        Count++;
        for(int i=0;i<vertexNum;i++){
            if(i!=start){
                dis[i]=dis[i]<dis[temp]+map[temp][i]?dis[i]:dis[temp]+map[temp][i];
            }
        }
        cout<<"--------------"<<endl;
        for(int i=0;i<vertexNum;i++){
            if(dis[i]==INF){
                cout<<"INF"<<' ';
            }
            else{
                cout<<dis[i]<<' ';
            }
        }
        cout<<endl;
    }
}
int main(void){
    getEdge();
    dijkstra(0);
}
