#include <iostream>
#include <time.h>                                   //引入计时头文件
#include <stdlib.h>
#define MAX 0x7fffffff                              //定义无穷大数
using namespace std;
int myTemp[10000];                                  //临时暂用数组1
int myTemp1[10000];                                 //临时暂用数组2
int Count=0;                                        //记录交换数的次数
class mySystem{                                     //抽象出整个程序系统
public:
    mySystem();
    ~mySystem(){};
    void processing();                                  //运行排序系统
    void randomGenerate(int num);                       //随机产生随机数
    int* getNums(){return numbers;}                     //获得需要排序的数组
    int* bubbleSort(int Nums[],int length);             //冒泡排序
    int* simSelSort(int Nums[],int length);             //简单选择排序
    int* insertSort(int Nums[],int length);             //插入排序
    void heapSort(int Nums[],int length);               //堆排序
    int* shellSort(int Nums[],int length);              //希尔排序
    void mergeSort(int answers[],int start,int end);    //归并排序
    void quickSort(int answers[],int low,int high);     //快速排序
    int* radixSort(int Nums[],int length);              //桶排序
    int* Copy(int Nums[],int length);                   //获得原数组的拷贝
    void display(int* myArr);
private:
    int numbers[10000];                                 //保存产生的随机数组
    int num;                                            //产生的随机数个数
    void ajustDown(int Nums[],int i,int length);        //堆排序需要的自上而下的调整
    void buildMaxHeap(int Nums[],int length);           //堆排序需要的建立最大堆函数
    void QuickSort(int answer[],int low,int high);      //快速排序需要的递归调用函数
    void _Merge(int Nums[],int start,int middle,int end); //归并排序需要的子函数
    void MergeSort(int Nums[],int start,int end);         //归并排序需要调用的子函数
    int getMaxLen(int Nums[],int length);               //获得数组中数的最大长度
};
void mySystem::display(int* myArr) {
    cout<<'-'<<endl;
    for(int i=0;i<num;i++){
        cout<<myArr[i]<<' ';
    }
    cout<<endl;
}
mySystem::mySystem() {                                  //初始界面
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
        else{                                           //用于检查产生的随机数个数是否合法
            cout<<"输入的个数不符合标准，请输入1-10000间的数字"<<endl;
        }
    }
    randomGenerate(num);
}
void mySystem::randomGenerate(int num) {
    srand(time(NULL));                                  //用时间作为随机种子
    for(int i=0;i<num;i++){                             //产生num个随机数
                numbers[i]=rand();
    }
}
void mySystem::processing() {                           //处理所有的排序算法调用
    int operand=0;
    while(operand!=9){
        cout<<"请选择排序算法:";
        cin>>operand;
        if(operand<1||operand>9){                       //检查输入是否合法
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
            case 5:{                                    //拷贝数组以免排序时改变原数组顺序
                auto ptr=Copy(numbers,num);
                quickSort(ptr,0,num-1);
                free(ptr);
                break;
            }
            case 6:{                                    //拷贝数组以免排序时改变原数组顺序
                auto ptr=Copy(numbers,num);
                heapSort(ptr,num);
                free(ptr);
                break;
            }
            case 7:{                                    //拷贝数组以免排序时改变原数组顺序
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
int* mySystem::Copy(int Nums[],int length){             //拷贝数组并返回指向拷贝数组的指针
    auto ptr=(int*)malloc(sizeof(int)*length);
    for(int i=0;i<length;i++){
        ptr[i]=Nums[i];
    }
    return ptr;
}
int* mySystem::bubbleSort(int Nums[],int length){
    int* Answer=Copy(Nums,length);
    clock_t start,end;                              //开始计时时间和结束计时时间
    start=clock();                                  //记录开始时间
    for(int i=1;i<length;i++){                      
        for(int j=0;j<length-1;j++){
            if(Answer[i]<Answer[j]){                //如果这个数比之前那个数小就交换
                swap(Answer[i],Answer[j]);
                Count++;                            //交换一次计数器加一
            }
            else{
                break;
            }
        }
    }
    end=clock();                                    //记录结束时间
    double duration= (double)(end - start) / CLOCKS_PER_SEC;    //计算整个过程时间
    cout<<"冒泡排序所用时间："<<duration<<endl;
    cout<<"冒泡排序交换次数："<<Count<<endl;
    Count=0;                                        //计数器清零备下次使用
    return Answer;                                  //返回排序后数组并在主函数中释放内存
}
int* mySystem::simSelSort(int Nums[],int length){
    int* temp=Copy(Nums,length);
    int* answer=(int*)malloc(sizeof(int)*length);
    clock_t start,end;
    start=clock();
    for(int i=0;i<length;i++){
        int min=MAX,index=0;                        //将最小数设为无穷大数
        for(int j=0;j<length;j++){                  //从所有数中寻找最小数保存其下标
            if(temp[j]<min){
                min=temp[j];
                index=j;                            //保存最小数下标
            }
        }
        answer[i]=min;                              //将最小数赋值给我们排到的位置
        Count++;                                    //计数器加一
        temp[index]=MAX;                            //将原来的那个最小数作废（设为无穷大数）
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
        if(answer[i]<answer[i-1]){                      //如果当前位置数比他之前的数小
            int guard=answer[i];                        //将当前位置的数设置为哨兵                  
            int j=i-1;                                  //从它前面的那个数开始比较
            while(guard<answer[j]&&j){                  //如果该数比它前面那个数小就与前面那个数交换
                Count++;                                //计数器加一
                answer[j+1]=answer[j];                  //交换两个数
                j--;                                    //接着寻找下一个数
            }
            Count++;                                    //循环里少加了一次计数
            answer[j+1]=guard;                          //将哨兵赋值到排序好的位置
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
    int temp=Nums[i];                                           //取其根节点
    for(int largest=2*i+1;largest<length;largest=largest*2+1){  //一直调整到根节点
        if(largest!=length-1&&Nums[largest]<Nums[largest+1]){   //如果其右子树的值比左子树的值大就取右子树
            largest++;                                          //否则取左子树值（即取子树最大的值）
        }
        if(temp<Nums[largest]){                                 //将子树最大的值与其父节点的值交换
            Nums[i]=Nums[largest];
            i=largest;
            Count++;                                            //计数器加一
        }
        else{
            break;
        }
    }
    Nums[i]=temp;                                               //将根节点复位
    Count++;                                                    //计数器加一
}
void mySystem::buildMaxHeap(int Nums[],int length){             //调用ajustdown函数构建最大堆
    for(int i=length/2-1;i>=0;i--){                             //从树的倒数第二层的第一个节点开始调整
        ajustDown(Nums,i,length);
    }
}
void mySystem::heapSort(int Nums[],int length){
    clock_t start,end;
    start=clock();
    buildMaxHeap(Nums,length);                                  //构造最大堆
    for(int i=length-1;i>0;i--){                                //每次移除一个数，然后接着构建最大堆
        swap(Nums[0],Nums[i]);                                  //将根节点放到末尾
        ajustDown(Nums,0,i);                                    //排序前n-1个数
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
    for(int gap=(length>>1);gap>0;(gap>>=1)){           //初始步长设为length/2，每次步长乘2
        for(int i=0;i<gap;i++){                         //即将整个数组分为length／2组排序
            for(int j=i+gap;j<length;j+=gap){
                if(answer[j]<answer[j-gap]){            //如果当前位置数比他之前的数小
                    int temp=answer[j];                 //设置哨兵
                    int pos=j-gap;
                    while(pos>=0&&answer[pos]>temp){    //步骤和插入排序一样，只是此时的步长为gap
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
    if(high-low<=0){                                    //没有需要排序的数就返回
        return;
    }
    int i=low,j=high;                                   //设置指向数组两头的指针
    int key=answer[i];                                  //key值取数组的第一个值
    while(i<j){                                         //当两个指针没有重合时
        while(i<j&&answer[j]>=key){                     //从后面开始寻找比key小的第一个数
            j--;
        }
        Count++;                                        ///////////////计数器加一
        answer[i]=answer[j];
        while(i<j&&answer[i]<=key){                     //从前面开始寻找比key大的第一个数
            i++;
        }
        Count++;                                        //计数器加一
        answer[j]=answer[i];
    }
    answer[i]=key;                                      //将key值复位
    QuickSort(answer,low,i-1);                          //将当前数组分成两组继续递归分组排序
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
    int first=start,index=start,second=middle+1;    //first指向第一个数组，second指向第二个数组
    while(first<=middle&&second<=end){              //两个数组的指针都没有指向该数组末尾时
        if(Nums[first]<Nums[second]){               //如果第一个数组的当前数比第二个数组的当前数小
            myTemp[index++]=Nums[first++];          //取第一个数组的当前数，并将第一个数组的指针向后移动一位
        }
        else{
            myTemp[index++]=Nums[second++];         //否则取第二个数组当前数，并将第二个数组的指针后移一位
        }
        Count++;                                    //计数器加一
    }
    while(first<=middle){                           //如果是第一个数组没有放完就把第一个数组的剩下所有数按顺序放进排序数组里
        myTemp[index++]=Nums[first++];
        Count++;
    }
    while(second<=end){                             //如果是第二个数组没有放完就把第二个数组的剩下所有数按顺序放进排序数组里
        myTemp[index++]=Nums[second++];
        Count++;
    }
    for(int i=start;i<=end;i++){                    //将暂存数组里的数拷贝回使用的数组里
        Nums[i]=myTemp[i];
    }
}
void mySystem::MergeSort(int Nums[],int start,int end){
    if(start>=end){
        return;
    }
    int middle=((start+end)>>1);                    //将数组均分为两份进行递归排序
    MergeSort(Nums,start,middle);
    MergeSort(Nums,middle+1,end);
    _Merge(Nums,start,middle,end);                  //将分成的两份排序好的数组归并
}
void mySystem::mergeSort(int Nums[],int start,int end){
    memset(myTemp,0,10000);                         //将临时数组清零
    clock_t begin,terminal;
    begin=clock();
    MergeSort(Nums,start,end);                      //调用归并排序
    terminal=clock();
    double duration= (double)(terminal - begin) / CLOCKS_PER_SEC;
    cout<<"归并排序所用时间："<<duration<<endl;
    cout<<"归并排序交换次数："<<Count<<endl;
    Count=0;
}
int mySystem::getMaxLen(int Nums[],int length){     
    int max=0,maxLen=0;
    for(int i=0;i<length;i++){                      //找到所有数中位数最长的那个
        if(Nums[i]>max){
            max=Nums[i];
        }
    }
    while(max){                                     //使用不断／10计算出其最大位数是maxLen
        max/=10;
        maxLen++;
    }
    return maxLen;                                  //返回该数组中的最长位数
}
int* mySystem::radixSort(int Nums[],int length){
    clock_t start,end;
    int* answer=Copy(Nums,length);
    int log=1,index=0;
    int* Element[10];                               //创建一个10*（length+1）的二维数组数组作为桶
    start=clock();
    int maxLen=getMaxLen(answer,length);
    for(int i=0;i<10;i++){                          //每行的长度都为length+1
        Element[i]=(int*)malloc(sizeof(int)*(1+length));
        Element[i][0]=0;                            //用每个桶的第一位存该桶内存储的数的数目
    }
    for(int q=0;q<maxLen;q++){
        for(int i=0;i<length;i++){
            int temp=++Element[(answer[i]/log)%10][0];  //计算出当前数所属的桶号
            Element[(answer[i]/log)%10][temp]=answer[i];    //放入桶中
        }
        for(int i=0,index=0;(i<10)&&(index<length);i++){
            for(int j=1;j<=Element[i][0];j++){
                answer[index++]=Element[i][j];          //按照桶的顺序将按照第q+1位大小排序后的数组放回answer中
            }
            Element[i][0]=0;                            //将二维数组的每行首位清零
        }
        log*=10;                                        //继续对下一个最高位进行排序
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