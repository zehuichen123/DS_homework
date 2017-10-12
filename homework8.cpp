#include <iostream>
#include <vector>
#define INF 0x7fffffff
using namespace std;
class Graph{
public:
    Graph();
    ~Graph(){};
    void Process();
    void CreateE();
    void CreateV();
    void Prim();
    void ShowTree();
    int getIndex(char name);
private:
    vector<char>primTree;
    int map[1000][1000];
    char char2Index[1000];
    int vNum;
};
Graph::Graph() {
    cout<<"**                  电网造价模拟系统               **"<<endl;
    cout<<"==================================================="<<endl;
    cout<<"**               A.---创建电网顶点                **"<<endl;
    cout<<"**               B.---添加电网的边                **"<<endl;
    cout<<"**               C.---构造最小生成树              **"<<endl;
    cout<<"**               D.---显示最小生成树              **"<<endl;
    cout<<"**               E.---退出程序                   **"<<endl;
    cout<<"=================================================="<<endl;
}

int Graph::getIndex(char name) {
    for(int i=0;i<vNum;i++){
        if(char2Index[i]==name){
            return i;
        }
    }
    return -1;
}
void Graph::CreateV() {
    cout<<"请输入顶点的个数：";
    cin>>vNum;
    cout<<"请依次输入各顶点的名称：";
    getchar();
    for(int i=0;i<vNum;i++){
        char2Index[i]=getchar();
        getchar();
    }
    cout<<endl;
}
void Graph::CreateE() {
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {
            map[i][j]=INF;
        }
    }
    for(int i=0;i<vNum*(vNum-1)/2;i++){
        cout<<"请输入两个顶点及边：";
        char vertex1,vertex2;
        getchar();
        vertex1=getchar();
        getchar();
        vertex2=getchar();
        cout<<vertex1<<" "<<vertex2<<endl;
        int index1=getIndex(vertex1),index2=getIndex(vertex2);
        if(index1<0||index2<0){
            cout<<"the vertex doesn't exist! Please reinput!"<<endl;
            i--;
            continue;
        }
        else{
            cin>>map[index1][index2];
            map[index2][index1]=map[index1][index2];
        }
    }
}
void Graph::Prim() {
    while(!primTree.empty())primTree.pop_back();     //清空原先prim树
    bool visited[vNum];
    memset(visited,false,vNum);
    cout<<"请输入起始顶点:";
    char start;
    cin>>start;
    primTree.push_back(start);
    for(int i=0;i<vNum-1;i++){
        int vertex=getIndex(primTree.back());
        int vMin=INF,temp;
        for(int i=0;i<vNum;i++){
            if(map[vertex][i]<vMin&&!visited[i]){
                vMin=map[vertex][i];
                temp=i;
            }
        }
        visited[temp]=true;
        primTree.push_back(char2Index[temp]);
    }
}
void Graph::ShowTree() {
    for(int i=0;i<primTree.size()-1;i++){
        auto first=primTree[i];
        //primTree.pop_back();
        auto second=primTree[i+1];
        int vIndex1=getIndex(first),vIndex2=getIndex(second);
        cout<<first<<"-<"<<map[vIndex1][vIndex2]<<">-"<<second<<"  ";
    }
    cout<<endl;
}
void Graph::Process() {
    char operand='\0';
    while(operand!='E'){
        cout<<"请选择操作: ";
        cin>>operand;
        switch (operand){
            case 'A':{
                CreateV();
                break;
            }
            case 'B':{
                CreateE();
                break;
            }
            case 'C':{
                Prim();
                break;
            }
            case 'D':{
                ShowTree();
                break;
            }
            case 'E':{
                break;
            }
            default:{
                cout<<"your input is not format-correct,please reinput!"<<endl;
            }
        }
    }
}
int main(void){
    Graph myGraph;
    myGraph.Process();
}