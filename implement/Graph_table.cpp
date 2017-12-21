/* this is a simple graph table
 * which use linklist to store 
 * every node's head.
 * Oct.6.2017
 */


#include <iostream>
using namespace std;
class Node{
public:
    Node():next(NULL){}
    int vertex;
    Node* next;
};
class Graph{
public:
    Graph(){}
    ~Graph(){}
    void Insert(bool a,int x,int y);
    void showGraph(int y);
    void setLinkTable(int x,int y);
    Node* getLinkTable(int x);
private:
    Node* linkTable[100];
};
Node* Graph::getLinkTable(int x){
    return linkTable[x];
}
void Graph::setLinkTable(int x,int y){
    auto ptr=new Node;
    ptr->vertex=y;
    linkTable[x]=ptr;
}
void Graph::Insert(bool a, int x, int y) {
    auto addr=getLinkTable(x);
    if(addr){
        while(addr->next){
            addr=addr->next;
        }
        auto temp=new Node;
        temp->vertex=y;
        addr->next=temp;
    }
    else{
        setLinkTable(x,y);
    }
    if(a==1){
        auto addr1=getLinkTable(y);
        if(addr1){
            while(addr1->next){
                addr1=addr1->next;
            }
            auto temp=new Node;
            temp->vertex=x;
            addr1->next=temp;
        }
        else{
            setLinkTable(y,x);
        }
    }
}
void Graph::showGraph(int y) {
    for(int i=0;i<y;i++) {
        cout << i << ':' << ' ';
        auto ptr=getLinkTable(i);
        if(ptr){
            do{
                cout<<ptr->vertex<<' ';
                ptr=ptr->next;
            }while(ptr);
        }
        cout<<endl;
    }
}
int main(void){
    Graph myGraph;
    int x,y;
    cin>>x>>y;
    for(int i=0;i<y;i++){
        int a,xx,yy;
        cin>>a>>xx>>yy;
        myGraph.Insert(a,xx,yy);
    }
    myGraph.showGraph(y);
}