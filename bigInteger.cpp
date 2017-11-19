#include <iostream>
#include <vector>
using namespace std;
class BigInteger{
public:
    BigInteger();
    BigInteger(const long long bigNum);
    BigInteger(const string bigNum);
    ~BigInteger(){}
    BigInteger operator =(const long long bigNum);
    BigInteger operator =(const string bigNum);
    BigInteger operator =(const BigInteger bigNum);
    BigInteger operator +(const long long bigNum);
    BigInteger operator +(const string bigNum);
    BigInteger operator +(const BigInteger bigNum);
    BigInteger operator +=(const long long bigNum);
    BigInteger operator +=(const string bigNum);
    BigInteger operator +=(const BigInteger bigNum);
    BigInteger operator -(const long long bigNum);
    BigInteger operator -(const string bigNum);
    BigInteger operator -(const BigInteger bigNum);
    BigInteger operator -=(const long long bigNum);
    BigInteger operator -=(const string bigNum);
    BigInteger operator -=(const BigInteger bigNum);
    void check();                                  //prevent appearing -0 situation
    void print(unsigned int digits=0);               //cout the first digits of BigInteger bigNumber with 10E
private:
    bool posOrNeg;                      //0 stands for positive,1 stands for negative
    vector<int>bigNumArr;
};
BigInteger::BigInteger():posOrNeg(0){
    bigNumArr.push_back(0);
}
BigInteger::BigInteger(const long long bigNum):posOrNeg(0) {
    *this=bigNum;
}
BigInteger::BigInteger(const string bigNum):posOrNeg(0) {
    *this=bigNum;
}
BigInteger BigInteger::operator=(const long long bigNum) {
    long long temp=bigNum;
    if(bigNum<0){
        posOrNeg=1;
        temp=-temp;
    }
    do{
        bigNumArr.push_back(temp%10);
        temp/=10;
    }while(temp>0);
    return *this;
}
BigInteger BigInteger::operator=(const BigInteger bigNum) {
    this->bigNumArr=bigNum.bigNumArr;
    this->posOrNeg=bigNum.posOrNeg;
    return *this;
}
BigInteger BigInteger::operator=(const string bigNum) {
    if(bigNum[0]=='-'){
        posOrNeg=1;
    }
    int i;                              //i here is a traverse variable
    for(i=bigNum.size()-1;i>=1;i--){
        bigNumArr.push_back(bigNum[i]-'0');
    }
    if(!posOrNeg){                      //if the first digit is '-'
        bigNumArr.push_back(bigNum[i]-'0');
    }
    return *this;
}
BigInteger BigInteger::operator+(const BigInteger bigNum) {
    //for three conditions: ++/+-/--
    BigInteger tempNum=bigNum;
    if(tempNum.posOrNeg^this->posOrNeg){
        if(tempNum.posOrNeg){
            tempNum.posOrNeg=0;
            return *this-tempNum;
        }
        else{
            BigInteger tempNumThis=*this;
            tempNumThis.posOrNeg=0;
            return tempNum-tempNumThis;
        }
    }
    else if(tempNum.posOrNeg&this->posOrNeg){
        unsigned int ptrDigits=0;
        auto preNumDigits=this->bigNumArr.size();
        auto lateNumDigits=tempNum.bigNumArr.size();
        bool getDigit=0;
        if(preNumDigits>=lateNumDigits){
            for(;ptrDigits<lateNumDigits;ptrDigits++){
                int tempAdd=this->bigNumArr[ptrDigits]+tempNum.bigNumArr[ptrDigits]+getDigit;
                this->bigNumArr[ptrDigits]=tempAdd%10;
                getDigit=tempAdd/10;
            }
            for(;ptrDigits<preNumDigits;ptrDigits++){
                int tempAdd=this->bigNumArr[ptrDigits]+getDigit;
                this->bigNumArr[ptrDigits]=tempAdd%10;
                getDigit=tempAdd/10;
            }
        }
        else{
            for(;ptrDigits<preNumDigits;ptrDigits++){
                int tempAdd=this->bigNumArr[ptrDigits]+tempNum.bigNumArr[ptrDigits]+getDigit;
                this->bigNumArr[ptrDigits]=tempAdd%10;
                getDigit=tempAdd/10;
            }
            for(;ptrDigits<lateNumDigits;ptrDigits++){
                int tempAdd=tempNum.bigNumArr[ptrDigits]+getDigit;
                this->bigNumArr.push_back(tempAdd%10);
                getDigit=tempAdd/10;
            }
        }
        return *this;
    }
    else{
        BigInteger tempNum1=*this;
        tempNum.posOrNeg=0;tempNum1.posOrNeg=0;
        *this=tempNum+tempNum1;
        this->posOrNeg=1;
        return *this;
    }
}
BigInteger BigInteger::operator+(const long long bigNum) {
    BigInteger tempNum(bigNum);
    return *this+tempNum;
}
BigInteger BigInteger::operator+(const string bigNum) {
    BigInteger tempNum(bigNum);
    return *this+tempNum;
}
BigInteger BigInteger::operator-(const BigInteger bigNum) {
    
}
void BigInteger::print(unsigned int digits) {
    if(digits==0){
        digits=bigNumArr.size();
    }
    if(posOrNeg){
        cout<<'-';
    }
    for(int i=digits-1;i>=0;i--){
        cout<<bigNumArr[i];
    }
}

int main(void) {
    BigInteger myNum1("4365465477673");
    auto myNum2 = myNum1;
    (myNum2 + 43543).print();
    cout<<endl;
    cout << 4365465477673 + 43543 << endl;
}