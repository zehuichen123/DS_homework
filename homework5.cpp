#include <iostream>
#include <fstream>
using namespace std;
ifstream openFile;               //定义文件输出流
bool checkOption(){              //询问用户是否想重新输入
    cout<<"Do you want to reinput?(y/n)"<<endl;
    char option;
    cin>>option;
    if(option=='y'){
        return 1;
    }
    else {
        return 0;
    }
}
void Count(){
    int countNum=0;
    cout<<"please input the word you want to count:";
    string word;                 //保存输入的单词
    cin>>word;
    string temp;                 //保存从文本中每次读入的单词
    while(openFile>>temp){
        if(temp==word){          //每次出现一次就将计数器加1
            countNum++;
        }
    }
    cout<<"该单词出现了"<<countNum<<"次"<<endl;
}
void Find(){
    cout<<"please input the word you want to count:";
    string word;                 //保存想要搜索的单词
    cin>>word;
    int lineNum=1,pos=0;
    string line;
    while(getline(openFile,line)){      //每次读入一行
        while((pos=line.find(word,pos))!=string::npos
            &&(line[pos+word.size()]==' '||line[pos+word.size()]=='\n')){     
                                                            //在每一行中重复寻找是否存在该单词
                                                            //pos代表当前行寻找到的位置
            cout<<"find word "<<'\''<<word<<'\''<<" at line "<<lineNum<<",column "<<pos<<endl;
            pos+=word.size();
        }
        lineNum++;
        pos=0;                          //将每一行寻找到的位置重置为0                  
    }
}
int main(void){
    bool check=1;
    while(check){
        cout<<"please input the name of file you want to open"<<endl;
        string fileName;
        cin>>fileName;
        openFile.open(fileName);
        if(openFile.is_open()){         //如果文件正常打开就执行操作
            bool check1=1;
            while(check1){
                //getchar();
                openFile.clear();
                openFile.seekg(0,ios::beg);     //每次进行使用时将读入指针重置为首位
                char option;
                cout<<"------------------------"<<endl;
                cout<<"选项1：对给定单词计数"<<endl;
                cout<<"选项2：检索给定单词"<<endl;
                cout<<"选项3：退出程序"<<endl;
                cout<<"请输入你的选择:";
                cin>>option;
                if(option=='1'){
                    Count();
                }
                else if(option=='2'){
                    Find();
                }
                else if(option=='3'){
                    return 0;
                }
                else{
                    cout<<"the input is not 1/2"<<endl;
                    check1=checkOption();
                }
            }
        }
        else{
            cout<<"can not find/open this file"<<endl;
            check=checkOption();
        }
    }

}