#include <iostream>
using namespace std;
class Heap{
public:
    Heap();
    ~Heap();
    int getHead(){return heapArr[1];}
    int getSize(){return Size;}
    void popHead();
    void Insert(int num);
    void buildHeap(int* myArr,int _size);
    void display();
private:
    void adjustDown(int pos);
    void adjustUp(int pos);
    int heapArr[1000];
    int Size;
};
Heap::Heap() {
}
Heap::~Heap() {
}
void Heap::Insert(int num) {
    Size++;
    heapArr[Size]=num;
    adjustUp(Size);
}
void Heap::buildHeap(int *myArr, int _size) {
    Size=_size;
    memcpy(heapArr+1,myArr,_size*sizeof(int));
    display();
    for(int i=_size/2;i>=1;i--){
        adjustDown(i);
    }
}
void Heap::adjustDown(int pos) {
    int flag=0,temp=2*pos;
    while(pos*2<=getSize()&&!flag){
        if(pos*2+1<=getSize()){
            if(heapArr[2*pos+1]>heapArr[pos*2]){
                temp=2*pos;
            }
            else{
                temp=2*pos+1;
            }
        }
        if(heapArr[pos]>heapArr[temp]){
            swap(heapArr[pos],heapArr[temp]);
            pos=temp;
        }
        else{
            flag=1;
        }
    }
}
void Heap::adjustUp(int pos) {
    int flag=0,temp;
    while(pos!=1&&!flag){
        if(heapArr[pos]<heapArr[pos/2]){
            swap(heapArr[pos],heapArr[pos/2]);
            pos/=2;
        }
        else{
            flag=1;
        }
    }
}
void Heap::popHead() {
    heapArr[1]=heapArr[Size];
    Size--;
    adjustDown(1);
}
void Heap::display() {
    for(int i=0;i<Size;i++){
        cout<<heapArr[i+1]<<' ';
    }
    cout<<endl;
}
int main(void){
    int m[10]={21,424,456,34,233,545,757,8786,353,42};
    Heap myHeap;
    myHeap.buildHeap(m,10);
    myHeap.display();
    for(int i=0;i<10;i++){
        cout<<myHeap.getHead()<<endl;
        myHeap.popHead();
    }
}