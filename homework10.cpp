#include <iostream>
#include <time.h>
#include <stdlib.h>
#define MAX 0x7fffffff
using namespace std;
int myTemp[10000];
int myTemp1[10000];
int Count=0;
class mySystem{
public:
    mySystem();
    ~mySystem(){};
    void processing();
    void randomGenerate(int num);
    int* getNums(){return numbers;}
    int* bubbleSort(int Nums[],int length);
    int* simSelSort(int Nums[],int length);
    int* insertSort(int Nums[],int length);
    void heapSort(int Nums[],int length);
    int* shellSort(int Nums[],int length);
    void mergeSort(int answers[],int start,int end);
    void quickSort(int answers[],int low,int high);
    int* radixSort(int Nums[],int length);
    int* Copy(int Nums[],int length);
private:
    int numbers[10000];
    int num;
    void ajustDown(int Nums[],int i,int length);
    void buildMaxHeap(int Nums[],int length);
    void QuickSort(int answer[],int low,int high);
    void _Merge(int Nums[],int start,int middle,int end);
    void MergeSort(int Nums[],int start,int end);
    int getMaxLen(int Nums[],int length);
};
mySystem::mySystem() {
    cout<<"**                  排序算法比较                   **"<<endl;
    cout<<"==================================================="<<endl;
    cout<<"**               1.---冒泡排序                    **"<<endl;
    cout<<"**               2.---选择排序                    **"<<endl;
    cout<<"**               3.---直接插入排序                 **"<<endl;
    cout<<"**               4.---希尔排序                    **"<<endl;
    cout<<"**               5.---快速排序                    **"<<endl;
    cout<<"**               6.---堆排序                      **"<<endl;
    cout<<"**               7.---归并排序                    **"<<endl;
    cout<<"**               8.---基数排序                    **"<<endl;
    cout<<"**               9.---退出程序                    **"<<endl;
    cout<<"=================================================="<<endl;
    int check=1;
    while(check){
        cout<<"请输入要产生的随机数个数：";
        cin>>num;
        if(num>0&&num<=10000){
            check=0;
        }
        else{
            cout<<"输入的个数不符合标准，请输入1-10000间的数字"<<endl;
        }
    }
    randomGenerate(num);
}
void mySystem::randomGenerate(int num) {
    srand(time(NULL));
    for(int i=0;i<num;i++){
        numbers[i]=rand();
    }
}
void mySystem::processing() {
    int operand=0;
    while(operand!=9){
        cout<<"请选择排序算法:";
        cin>>operand;
        if(operand<1||operand>9){
            cout<<"您输入的数字不在1-9之间，请重新输入"<<endl;
            continue;
        }
        switch (operand){
            case 1:{
                auto ptr=bubbleSort(numbers,num);
                free(ptr);
                break;
            }
            case 2:{
                auto ptr=simSelSort(numbers,num);
                free(ptr);
                break;
            }
            case 3:{
                auto ptr=insertSort(numbers,num);
                free(ptr);
                break;
            }
            case 4:{
                auto ptr=shellSort(numbers,num);
                free(ptr);
                break;
            }
            case 5:{
                auto ptr=Copy(numbers,num);
                quickSort(ptr,0,num-1);
                free(ptr);
                break;
            }
            case 6:{
                auto ptr=Copy(numbers,num);
                heapSort(ptr,num);
                free(ptr);
                break;
            }
            case 7:{
                auto ptr=Copy(numbers,num);
                mergeSort(ptr,0,num-1);
                free(ptr);
                break;
            }
            case 8:{
                auto ptr=radixSort(numbers,num);
                free(ptr);
                break;
            }
        }
    }
}
int* mySystem::Copy(int Nums[],int length){
    auto ptr=(int*)malloc(sizeof(int)*length);
    for(int i=0;i<length;i++){
        ptr[i]=Nums[i];
    }
    return ptr;
}
int* mySystem::bubbleSort(int Nums[],int length){
    int* Answer=Copy(Nums,length);
    clock_t start,end;
    start=clock();
    for(int i=1;i<length;i++){
        for(int j=0;j<length-1;j++){
            if(Answer[i]<Answer[j]){
                swap(Answer[i],Answer[j]);
                Count++;
            }
        }
    }
    end=clock();
    double duration= (double)(end - start) / CLOCKS_PER_SEC;
    cout<<"冒泡排序所用时间："<<duration<<endl;
    cout<<"冒泡排序交换次数："<<Count<<endl;
    Count=0;
    return Answer;
}
int* mySystem::simSelSort(int Nums[],int length){
    int* temp=Copy(Nums,length);
    int* answer=(int*)malloc(sizeof(int)*length);
    clock_t start,end;
    start=clock();
    for(int i=0;i<length;i++){
        int min=MAX,index=0;
        for(int j=0;j<length;j++){
            if(temp[j]<min){
                min=temp[j];
                index=j;
                Count++;
            }
        }
        answer[i]=min;
        temp[index]=MAX;
    }
    end=clock();
    free(temp);
    double duration= (double)(end - start) / CLOCKS_PER_SEC;
    cout<<"选择排序所用时间："<<duration<<endl;
    cout<<"选择排序交换次数："<<Count<<endl;
    Count=0;
    return answer;
}
int* mySystem::insertSort(int Nums[],int length){
    int* answer=Copy(Nums,length);
    clock_t start,end;
    start=clock();
    for(int i=1;i<length;i++){
        if(answer[i]<answer[i-1]){
            int guard=answer[i];
            int j=i-1;
            while(guard<answer[j]){
                Count++;
                answer[j+1]=answer[j];
                j--;
            }
            Count++;
            answer[j+1]=guard;
        }
    }
    end=clock();
    double duration= (double)(end - start) / CLOCKS_PER_SEC;
    cout<<"选择排序所用时间："<<duration<<endl;
    cout<<"选择排序交换次数："<<Count<<endl;
    Count=0;
    return answer;
}

void mySystem::ajustDown(int Nums[],int i,int length){
    int temp=Nums[i];
    for(int largest=2*i+1;largest<length;largest=largest*2+1){
        if(largest!=length-1&&Nums[largest]<Nums[largest+1]){
            largest++;
        }
        if(temp<Nums[largest]){
            Nums[i]=Nums[largest];
            i=largest;
            Count++;
        }
        else{
            break;
        }
    }
    Nums[i]=temp;
    Count++;
}
void mySystem::buildMaxHeap(int Nums[],int length){
    for(int i=length/2-1;i>=0;i--){
        ajustDown(Nums,i,length);
    }
}
void mySystem::heapSort(int Nums[],int length){
    clock_t start,end;
    start=clock();
    buildMaxHeap(Nums,length);
    for(int i=length-1;i>0;i--){
        swap(Nums[0],Nums[i]);
        ajustDown(Nums,0,i);
    }
    end=clock();
    double duration= (double)(end - start) / CLOCKS_PER_SEC;
    cout<<"堆排序所用时间："<<duration<<endl;
    cout<<"堆排序交换次数："<<Count<<endl;
    Count=0;
}
int* mySystem::shellSort(int Nums[],int length){
    clock_t start,end;
    start=clock();
    int* answer=Copy(Nums,length);
    for(int gap=(length>>1);gap>0;(gap>>=1)){
        for(int i=0;i<gap;i++){
            for(int j=i+gap;j<length;j+=gap){
                if(answer[j]<answer[j-gap]){
                    int temp=answer[j];
                    int pos=j-gap;
                    while(pos>=0&&answer[pos]>temp){
                        Count++;
                        answer[pos+gap]=answer[pos];
                        pos-=gap;
                    }
                    Count++;
                    answer[pos+gap]=temp;
                }
                Count++;
            }
        }
    }
    end=clock();
    double duration= (double)(end - start) / CLOCKS_PER_SEC;
    cout<<"希尔排序所用时间："<<duration<<endl;
    cout<<"希尔排序交换次数："<<Count<<endl;
    Count=0;
    return answer;
}
void mySystem::QuickSort(int answer[],int low,int high){
    if(high-low<=0){
        return;
    }
    int i=low,j=high;
    int key=answer[i];
    while(i<j){
        while(i<j&&answer[j]>=key){
            j--;
        }
        Count++;
        answer[i]=answer[j];
        while(i<j&&answer[i]<=key){
            i++;
        }
        Count++;
        answer[j]=answer[i];
    }
    answer[i]=key;
    QuickSort(answer,low,i-1);
    QuickSort(answer,i+1,high);
}
void mySystem::quickSort(int answer[],int low,int high){
    clock_t start,end;
    start=clock();
    QuickSort(answer,low,high);
    end=clock();
    double duration= (double)(end - start) / CLOCKS_PER_SEC;
    cout<<"快速排序所用时间："<<duration<<endl;
    cout<<"快速排序交换次数："<<Count<<endl;
    Count=0;
}
void mySystem::_Merge(int Nums[],int start,int middle,int end){
    if(end-start<=0){
        return;
    }
    int first=start,index=start,second=middle+1;
    while(first<=middle&&second<=end){
        if(Nums[first]<Nums[second]){
            myTemp[index++]=Nums[first++];
        }
        else{
            myTemp[index++]=Nums[second++];
        }
        Count++;
    }
    while(first<=middle){
        myTemp[index++]=Nums[first++];
        Count++;
    }
    while(second<=end){
        myTemp[index++]=Nums[second++];
        Count++;
    }
    for(int i=start;i<=end;i++){
        Nums[i]=myTemp[i];
    }
}
void mySystem::MergeSort(int Nums[],int start,int end){
    if(start>=end){
        return;
    }
    int middle=((start+end)>>1);
    MergeSort(Nums,start,middle);
    MergeSort(Nums,middle+1,end);
    _Merge(Nums,start,middle,end);
}
void mySystem::mergeSort(int Nums[],int start,int end){
    memset(myTemp,0,10000);
    clock_t begin,terminal;
    begin=clock();
    MergeSort(Nums,start,end);
    terminal=clock();
    double duration= (double)(terminal - begin) / CLOCKS_PER_SEC;
    cout<<"归并排序所用时间："<<duration<<endl;
    cout<<"归并排序交换次数："<<Count<<endl;
    Count=0;
}
int mySystem::getMaxLen(int Nums[],int length){
    int max=0,maxLen=0;
    for(int i=0;i<length;i++){
        if(Nums[i]>max){
            max=Nums[i];
        }
    }
    while(max){
        max/=10;
        maxLen++;
    }
    return maxLen;
}
int* mySystem::radixSort(int Nums[],int length){
    clock_t start,end;
    int* answer=Copy(Nums,length);
    int log=1,index=0;
    int* Element[10];
    start=clock();
    int maxLen=getMaxLen(answer,length);
    for(int i=0;i<10;i++){
        Element[i]=(int*)malloc(sizeof(int)*(1+length));
        Element[i][0]=0;
    }
    for(int q=0;q<maxLen;q++){
        for(int i=0;i<length;i++){
            int temp=++Element[(answer[i]/log)%10][0];
            Element[(answer[i]/log)%10][temp]=answer[i];
        }
        for(int i=0,index=0;(i<10)&&(index<length);i++){
            for(int j=1;j<=Element[i][0];j++){
                answer[index++]=Element[i][j];
            }
            Element[i][0]=0;
        }
        log*=10;
    }
    end=clock();
    double duration= (double)(end - start) / CLOCKS_PER_SEC;
    cout<<"基数排序所用时间："<<duration<<endl;
    cout<<"基数排序交换次数："<<Count<<endl;
    Count=0;
    return answer;
}

int main(void){
    mySystem mySystem1;
    mySystem1.processing();
}