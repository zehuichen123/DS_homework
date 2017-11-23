/*迷宫问题
 *入口为左上角
 *出口为右下角
 *'#'为可走，'*'为不可走
*/
#include <iostream>
#include <vector>
using namespace std;
char map[7][7]={                        //内置地图
        '#','#','#','*','#','#','#',
        '#','*','#','*','*','*','#',
        '*','*','#','#','#','#','#',
        '#','*','*','*','#','*','#',
        '*','*','#','*','*','*','#',
        '#','*','#','*','#','*','#',
        '#','#','#','#','#','#','#'
};
int xx[4]={1,0,-1,0};                   //定义四个方向的bias，方便搜索时用for循环代替
int yy[4]={0,1,0,-1};                   //同上

class point{                            //定义搜索顶点的类
public:
    int x;
    int y;
};

vector<point>answer;                    //储存搜索的路径
void display(){                         //打印路线图
    int count=0;
    cout<<"迷宫路径:"<<endl;
    for(auto i:answer){
        cout<<'('<<i.x+1<<','<<i.y+1<<')';
        count++;
        if(count!=answer.size()){       //防止在最后一个顶点时打印出--->
            cout<<"--->";
        }
    }
}
void dfs(){                             //深度优先搜索函数
    auto Point=answer.back();           //获得路径的上一步顶点
    int PointX=Point.x;
    int PointY=Point.y;
    if(!((PointX==6&&PointY==6))){          //如果没有到达出口就继续寻找
        for(int i=0;i<4;i++){               //对四个加bias进行方向搜索
            int X=PointX+xx[i];
            int Y=PointY+yy[i];
            if(X>=0&&X<7&&Y>=0&&Y<7) {      //检测是否超出边界
                if (map[X][Y] == '#') {     //如果探测的此顶点可行就加入answer中
                    auto ptr = new point;
                    ptr->x = X;
                    ptr->y = Y;
                    answer.push_back(*ptr);
                    map[X][Y] = '*';        //把加入的顶点设为不可走防止后来重复搜索
                    dfs();
                    map[X][Y] = '#';        //如果返回后重新设为可走
                }
            }
        }
        map[PointX][PointY]='*';            //如果四个方向都走不通就返回并把该顶点设为不可走因为搜索过不通       
        answer.pop_back();                  //从answer中取出该节点
        return;
    }
    else{
        display();                              //如果到达出口则打印路径
        exit(0);
    }
}
int main(void){
    int PointX=0,PointY=0;
    auto ptr=new point;                     //此处将开始节点放入answer中
    ptr->x=PointX;
    ptr->y=PointY;
    answer.push_back(*ptr);
    map[PointX][PointY]='*';                //将开始节点设为不可走
    dfs();                                  //调用dfs进行搜索路径      
    cout<<"unable to find a path :("<<endl;    
}
