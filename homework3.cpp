#include <iostream>
#include <vector>
using namespace std;
char map[7][7]={
        '#','#','#','#','#','#','#',
        '#','*','#','*','*','*','#',
        '#','*','#','*','#','#','#',
        '#','*','*','*','#','*','#',
        '#','*','#','*','*','*','#',
        '#','*','#','*','#','*','#',
        '#','#','#','#','#','#','#'
};
int xx[4]={1,0,-1,0};
int yy[4]={0,1,0,-1};

class point{
public:
    int x;
    int y;
};

vector<point>answer;
void display(){
    int count=0;
    cout<<"迷宫路径:"<<endl;
    for(auto i:answer){
        cout<<'('<<i.x+1<<','<<i.y+1<<')';
        count++;
        if(count!=answer.size()){
            cout<<"--->";
        }
    }
}
void dfs(){
    auto Point=answer.back();
    int PointX=Point.x;
    int PointY=Point.y;
    while(!((PointX==6&&PointY==6))){
        for(int i=0;i<4;i++){
            int X=PointX+xx[i];
            int Y=PointY+yy[i];
            if(X>=0&&X<7&&Y>=0&&Y<7) {
                if (map[X][Y] == '#') {
                    auto ptr = new point;
                    ptr->x = X;
                    ptr->y = Y;
                    answer.push_back(*ptr);
                    dfs();
                } else {
                    answer.pop_back();
                    return;
                }
            }
        }
    }
    display();
    exit(1);
}
int main(void){
    cout<<"输入1为自带地图，输入2为自定义地图"<<endl;
    int PointX=0,PointY=0;
    auto ptr=new point;
    ptr->x=PointX;
    ptr->y=PointY;
    answer.push_back(*ptr);
    dfs();
}
