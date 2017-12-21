/*
adjecent matrix:
0 3 5 8 0
3 0 6 4 11
5 6 0 2 0
8 4 2 0 10
0 11 0 10 0

 */

#include <iostream>
#include <vector>
#define SIZE 15
#define INF 0x7fffffff
using namespace std;
int map[SIZE][SIZE];
bool used[SIZE];
vector<int>primTree;
int n;
void getMap(){
    cout<<"the number of vertex:";
    cin>>n;
    cout<<"input the edge in matrix"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>map[i][j];
            if(map[i][j]==0){
                map[i][j]=INF;
            }
        }
    }
}
void Prim(int start){
    primTree.push_back(start);              //put the first vertex into the tree
    used[start]=true;
    while(primTree.size()!=n){              //if not tranverse all vertexes, go on
        int temp=0;                         //save the chosen vertex number
        int lowEdge=INF;                    //find the lowest cost adjacent edge of known tree
        for(auto i:primTree){
            for(int j=0;j<n;j++){
                if(j!=i){
                    if(map[i][j]<lowEdge&&!used[j]){    //find the lowest cost edge and save it in temp
                        lowEdge=map[i][j];
                        temp=j;
                    }
                }
            }
        }
        used[temp]=true;                    //add this vertex to primTree and set the used array to true
        primTree.push_back(temp);
    }
}
int main(void){
    getMap();
    Prim(0);
    for(auto i:primTree){
        cout<<i<<' ';
    }
}
