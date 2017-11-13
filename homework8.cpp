#include <iostream>
#include <vector>
#define INF 0x7fffffff              //定义无穷大数为SIGNED INT的MAX
using namespace std;
class Graph{                        //定义图结构
public:
    Graph();
    ~Graph(){};
    void Process();                 //读入用户输入选项
    void CreateE();                 //创建电网的边
    void CreateV();                 //创建电网的顶点
    void Prim();                    //最小生成树算法
    void ShowTree();                //展示最小生成树
    int getIndex(char name);        //根据name获得树的节点
private:
    vector<char>primTree;           //储存最小树的路径
    int map[1000][1000];            //使用邻接表保存各个顶点之间的连接情况
    char char2Index[1000];          //保存从顶点映射成数字的规则
    int vNum;                       //保存所有顶点的个数
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
    for(int i=0;i<vNum;i++){           //从保存的节点中找到name的节点并返回对应的数字
        if(char2Index[i]==name){
            return i;
        }
    }
    return -1;                         //如果没有找到名字为name的顶点就返回-1
}
void Graph::CreateV() {
    cout<<"请输入顶点的个数：";
    cin>>vNum;
    cout<<"请依次输入各顶点的名称：";
    getchar();
    for(int i=0;i<vNum;i++){           //依次获得顶点的名称并将其对应成数字
        char2Index[i]=getchar();       //映射关系保存在char2Index数组中
        getchar();
    }
    cout<<endl;
}
void Graph::CreateE() {
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {
            map[i][j]=INF;             //这里将两个顶点没有通路时其权值为INF
        }
    }
    for(int i=0;i<vNum*(vNum-1)/2;i++){   //有vNum个顶点所以最多有vNum*(vNum-1)/2条边
        cout<<"请输入两个顶点及边：";
        char vertex1,vertex2;
        getchar();
        vertex1=getchar();
        getchar();
        vertex2=getchar();
        cout<<vertex1<<" "<<vertex2<<endl;
        int index1=getIndex(vertex1),index2=getIndex(vertex2);  //获得顶点对应的数字
        if(index1<0||index2<0){        //检查用户输入是否合法
            cout<<"the vertex doesn't exist! Please reinput!"<<endl;
            i--;
            continue;
        }
        else{
            cin>>map[index1][index2];
            map[index2][index1]=map[index1][index2];       //邻接矩阵为对称
        }
    }
}
void Graph::Prim() {
    while(!primTree.empty())primTree.pop_back();    //清空原先prim树
    bool visited[vNum];                             //用于保存该顶点是否已经被连接入树
    memset(visited,false,vNum);
    cout<<"请输入起始顶点:";
    char start;                                     //最小树开始的起点
    cin>>start;
    primTree.push_back(start);                      //将起点放入primTree中
    for(int i=0;i<vNum-1;i++){                      //从所有边中找出权值最小的边的另一个顶点
        int vertex=getIndex(primTree.back());
        int vMin=INF,temp;
        for(int i=0;i<vNum;i++){
            if(map[vertex][i]<vMin&&!visited[i]){
                vMin=map[vertex][i];
                temp=i;
            }
        }
        visited[temp]=true;                         //将该顶点设置为已经被并入树中
        primTree.push_back(char2Index[temp]);       //将该顶点放入primTree中作为最后答案
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