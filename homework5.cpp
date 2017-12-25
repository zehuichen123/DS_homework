#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;
map<string,int>fileSum;
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
void splitString(const string& s, vector<string>& v,char c){
    int pos1, pos2;
    pos2 = s.find(c);                   //找到c出现的位置
    pos1 = 0;
    while(string::npos != pos2)         //如果没有找到string的末尾则继续寻找
    {
        v.push_back(s.substr(pos1, pos2-pos1));     //将遇到space之前的字符作为一个单词放入vector中
        pos1 = pos2 + 1;                            //从下一个位置开始继续寻找c出现的位置
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())                          //将最后一段字符作为一个单词放入vector中
        v.push_back(s.substr(pos1));
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
void Summary(string fileName){
    fileSum.clear();            //将map清空
    int wordCount=0;            //统计所有单词量
    string line;                //每次读入一行句子
    string word;                //存放每行切分的所有单词
    while(getline(openFile,line)){
        vector<string>word;
        splitString(line,word,' ');
        wordCount+=word.size();
        for(auto i:word){           //如果单词的末尾是'.'就将其去除
            if(i[i.size()-1]=='.'){
                i.erase(i.end()-1);
            }
            fileSum[i]++;           //使用map统计总单词量
        }
    }
    cout<<"*******单词计数*********"<<endl;
    cout<<"单词        次数"<<endl;
    for(auto i:fileSum){
        cout<<i.first<<"       "<<i.second<<endl;
    }
    cout<<fileName<<"的单词总数为"<<wordCount<<endl;
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
void Create(){
    string fileName;
    cout << "请输入要新建的文件名：";
    cin >> fileName;
    ofstream fout(fileName);            //创建待写入数据文件
    bool goOn = 1;
    while (goOn) {
        cout<<"请输入一行文本:";
        getchar();                      //读入回车
        string line;
        char yOrn;
        getline(cin,line);
        fout << line+'\n';              //每次写入前将结尾加上‘/n'
        cout << "结束输入吗？y or n:";
        cin >> yOrn;
        if (yOrn == 'y') {
            break;
        }
    }
    fout.close();
}
int main(void) {
    cout << "**************************************" << endl;
    cout << "********文本文件单词的检索与计数**********" << endl;
    while (1) {
        cout << "**************************************" << endl;
        char operand;
        cout << "[1]建立文本文档" << endl;
        cout << "[2]文本单词汇总" << endl;
        cout << "[3]单词定位" << endl;
        cout << "[4]退出" << endl;
        cout << "请选择(1~4):";
        cin >> operand;
        switch (operand) {
            case '1': {
                Create();
                break;
            }
            case '2': {
                bool check=true;
                while(check){
                    cout<<"请输入要打开的文件名：";
                    string fileName;
                    cin >> fileName;
                    openFile.open(fileName);
                    if (openFile.is_open()) {         //如果文件正常打开就执行操作
                        bool check1 = 1;
                        while (check1) {
                            Summary(fileName);
                            break;
                        }
                        openFile.close();
                        break;
                    } else {
                        cout << "can not find/open this file" << endl;
                        check=checkOption();
                    }
                }
                break;
            }
            case '3': {
                bool check=true;
                while(check){
                    cout<<"请输入要打开的文件名：";
                    string fileName;
                    cin >> fileName;
                    openFile.open(fileName);
                    if (openFile.is_open()) {         //如果文件正常打开就执行操作
                        char aOrb;
                        cout << "文本文件单词的定位统计及定位" << endl;
                        cout << "a.单词出现次数" << endl;
                        cout << "b.单词出现位置" << endl;
                        cout << "请输入a或b:";
                        cin >> aOrb;
                        if (aOrb == 'a') {
                            Count();
                        } else {
                            Find();
                        }
                        openFile.close();
                        break;
                    } else {
                        cout << "can not find/open this file" << endl;
                        check=checkOption();
                    }
                }
                break;
            }
            case '4': {
                exit(0);
            }
        }
    }
}

