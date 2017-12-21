/*
vertex1 vertex2 edgeWeight
1 2 3
1 3 5
1 4 8
2 3 6
2 4 4
2 5 11
3 4 2
4 5 10
 */

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#define SIZE 15
#define INF 0x7fffffff
using namespace std;
int edgeNum;
int vertexNum;
int unionSet[SIZE];                     //use unionSet to judge the adjecent of map
int unionFind(int num){
    if(unionSet[num]!=num){
        unionSet[num]=unionFind(unionSet[num]);
    }
    return unionSet[num];
}

typedef struct edgeWeight{
    int vertex1;
    int vertex2;
    int weight;
}edgeWeight;
bool tmp(const edgeWeight a,const edgeWeight b){
    return a.weight<=b.weight;
}
vector<edgeWeight>map;
vector<edgeWeight>primTree;
void getEdge(){
    cout<<"the number of vertexes:";
    cin>>vertexNum;
    cout<<"the number of edges:";
    cin>>edgeNum;
    for(int i=0;i<edgeNum;i++){
        unionSet[i]=i;
    }
    cout<<"input the edge in matrix"<<endl;
    for(int i=0;i<edgeNum;i++){
        auto ptr=new edgeWeight;
        cin>>ptr->vertex1>>ptr->vertex2>>ptr->weight;
        map.push_back(*ptr);
    }
    sort(map.begin(),map.end(),tmp);            //sort the edge based on weight
}
void kruskal(){
    int Count=1;
    while(primTree.size()!=vertexNum-1){        //if hasn't find all edges that build the tree, go on
        while(1){
            auto minEdge=map[0];                //find the min edge weight
            auto vertexA=minEdge.vertex1;
            auto vertexB=minEdge.vertex2;
            if(unionFind(vertexA)!=unionFind(vertexB)){     //judge if the vertexes in this edge has
                                                            //already in one connected component.
                primTree.push_back(minEdge);
                unionSet[vertexA]=unionSet[vertexB];        //get them in one connected component
                break;
            }
            else{
                map.erase(map.begin());                     //otherwise, find the next min weight edge
                continue;
            }
        }
    }
}
int main(void){
    getEdge();
    kruskal();
    for(auto i:primTree){
        cout<<i.vertex1<<' '<<i.vertex2<<' '<<i.weight<<endl;
    }
}
