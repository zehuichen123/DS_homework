#include <iostream>
#include <fstream>
using namespace std;
ifstream openFile;
bool checkOption(){
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
    string word;
    cin>>word;
    string temp;
    while(openFile>>temp){
        if(temp==word){
            countNum++;
        }
    }
    cout<<"该单词出现了"<<countNum<<"次"<<endl;
}
void Find(){
    cout<<"please input the word you want to count:";
    string word;
    cin>>word;
    int lineNum=1,pos=0;
    string line;
    while(getline(openFile,line)){
        while((pos=line.find(word,pos))!=string::npos){
            cout<<"find word "<<'\''<<word<<'\''<<" at line "<<lineNum<<",column "<<pos<<endl;
            pos+=word.size();
        }
        lineNum++;
        pos=0;
    }
}
int main(void){
    bool check=1;
    while(check){
        cout<<"please input the name of file you want to open"<<endl;
        string fileName;
        cin>>fileName;
        openFile.open(fileName);
        if(openFile.is_open()){
            bool check1=1;
            while(check1){
                //getchar();
                openFile.clear();
                openFile.seekg(0,ios::beg);
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