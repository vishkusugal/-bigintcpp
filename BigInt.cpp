#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int WIDTH=4;
int toInt(char c){
    return ((int)c - 48);
}
string tostr(int a,int len){
    string s = to_string(a);
    int diff = len-s.size();
    if(diff>0){
        string s1 (diff,'0');
        return s1.append(s);
    }
    return s;
}

void removeZero(string &a){
   while(a.size()>1 && toInt(a[0])==0){
            a.erase(0,1);
        }
}

class BigIntCPP{
    public:
    string s;
    vector<int> xi;
    int word;
    int bytes;
    int len;
    BigIntCPP(string str);
    void printBigInt();
    BigIntCPP* mult(BigIntCPP *bi1);
    BigIntCPP* add(BigIntCPP *bi1);
};
BigIntCPP* BigIntArrToStr(vector<int> a){
    string s="";
    for(int i=a.size()-1;i>=0;i--){
        s.append(to_string(a[i]));
    }
    return new BigIntCPP(s);
}
BigIntCPP* BigIntCPP::add(BigIntCPP *bi1){
    vector<int> a = xi;
    vector<int> b = bi1->xi;
    unsigned int sum,carry=0;
    vector<int> c;
    int len1 = a.size();
    int len2 = b.size();
    int qm = pow(10,WIDTH);
    for(int i=0;i<len1;i++){
        sum = a[i]+b[i]+carry;
        carry = sum/qm;
        sum = sum%qm;
        c.push_back(sum);
    }
    if(carry>0){
        c.push_back(carry);
    }
    string str="";
    for(int i=len1+1;i>=0;i--){
        str.append(tostr(c[i],WIDTH));
    }
    removeZero(str);
    return new BigIntCPP(str);
}
BigIntCPP* BigIntCPP::mult(BigIntCPP *bi1){    
    vector<int> a = xi;
    vector<int> b = bi1->xi;
    unsigned long long prod,sum,carry=0;
    int len1 = a.size();
    int len2 = b.size();
    int qm = pow(10,WIDTH);
    unsigned int c[len1+len2]={};
    for(int i=0;i<len2;i++){
        carry=0;
        for(int j=0;j<len1;j++){
            prod = a[j]*b[i];
            sum = c[i+j]+prod+carry;
            carry = sum/qm;
            sum = sum%qm;
            c[i+j]=sum;
        }
        c[i+len1]=carry;
    }
    string str="";
    for(int i=len1+len2-1;i>=0;i--){
        str.append(tostr(c[i],WIDTH));
    }
    removeZero(str);
    return new BigIntCPP(str);
}
void BigIntCPP::printBigInt(){
    for(int i=0;i<bytes;i++){
        cout<<i<<":"<<xi[i]<<endl;
    }
}
BigIntCPP::BigIntCPP(string str){
    s=str; 
    word =WIDTH;
    len = s.size();
    bytes = ceil((float)len/word);
    for(int i=0;i<bytes;i++){
        int end = len-word*i;
        int start;
        int caplen =word;
        if(end>=word){
            start =end-word;   
        } else {
            start=0;
            caplen=end;
        }
        xi.push_back(stoi(s.substr(start,caplen)));
    }
}
void addString(string s1,string s2){
    
}

int main(){
    int n;
    cin >> n;
    //BigIntCPP *a1 = new BigIntCPP("2658271574788448768043625811014615890319638528000000000");
    //BigIntCPP *a2 = new BigIntCPP("5");
    
    //a1 = a1->mult(a2);
    //cout<<a1->s<<endl;
    
    BigIntCPP *b1 = new BigIntCPP("1");
    for(int i=2;i<=n;i++){
        //cout<<i-1<<"-->"<<b1->s<<endl;
        BigIntCPP *b2 = new BigIntCPP(tostr(i,WIDTH));
        b1 = b1->mult(b2);
    }
    cout<<b1->s<<endl;
    return 0;
}
