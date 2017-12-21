/* this is a simple graph matrix
 * with a simple insert manipulation
 * Oct.6th 2017
*/


#include <iostream>
#include <memory.h>
#define GraphSize 500
using namespace std;
class Graph{
public:
    Graph(){
        memset(Map,0,sizeof(Map));
    }
    ~Graph(){}
    void setMap(int x,int y){
        Map[x][y]=true;
    }
    void showMap(int x,int y){
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                cout<<Map[i][j]<<' ';
            }
            cout<<endl;
        }
    }
private:
    bool Map[GraphSize][GraphSize];
};
int main(void){
    Graph myGraph;
    int x,y;
    cin>>x>>y;
    for(int i=0;i<y;i++){
        int a,xx,yy;
        cin>>a>>xx>>yy;
        if(a==1){
            myGraph.setMap(xx,yy);
            myGraph.setMap(yy,xx);
        }
        else{
            myGraph.setMap(xx,yy);
        }
    }
    myGraph.showMap(x,y);
}