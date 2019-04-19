#include<bits/stdc++.h>
using namespace std;
//Tested for numbers less than 10^18
const int numbOfPrimes = 10;
const int primeNumb[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

long long int reduceAllTwos(long long int x){
    int p = 1, q = 57, s = (p+q)/2;
    while(p<q){
        s = (p+q)/2;
        if( x<=(1<<s) || x%(1<<s)==1 || (x/(1<<s))%2==1 )
            q = s;
        else
            p = s+1;
    }
    return x/(1<<p);
}

long long int multiplyMod(long long int x, long long int y, const long long int MOD){
    if(y == 1)
        return x%MOD;
    if(y%2 == 0 )
        return (multiplyMod(x,y/2, MOD)%MOD + multiplyMod(x,y/2, MOD)%MOD)%MOD;
    else
        return (multiplyMod(x,(y-1)/2, MOD)%MOD + multiplyMod(x,(y-1)/2, MOD)%MOD + x%MOD)%MOD;
}

long long int powerMod(long long int base, long long int exponent, const long long int MOD){
    if(exponent == 0 )
        return 1;
    if(exponent == 1)
        return base%MOD;
    if(exponent%2 == 1){
        return multiplyMod(powerMod(base, exponent-1, MOD)%MOD, base, MOD);
    }else{
        return multiplyMod(powerMod(base, exponent/2,MOD)%MOD,powerMod(base, exponent/2,MOD)%MOD,MOD);
    }

}

bool rabinMillerTest(long long int x, int testBase){
    long long int p = x;
    p--;
    p = reduceAllTwos(p);
    long long int lastTest = powerMod(testBase,p,x);
    if(lastTest==-1 || lastTest-x == -1 || lastTest == 1)
        return true;
    p*=2;
    while(p < x-1) {
        long long int test = multiplyMod(lastTest, lastTest, x);
        if(test == -1 || test-x == -1)
            return true;
        lastTest = test;
        p*=2;
    }
    return false;
}

bool prime(long long int x){
    if(x==1)
        return false;
    if(x==2)
        return true;
    if(x==3)
        return true;
    if(!(x%2))
        return false;
    for(int i = 0; i<numbOfPrimes; i++){
        if(x == primeNumb[i])
            return true;
        if(!rabinMillerTest(x,primeNumb[i]))
            return false;
    }
    return true;
}

int main() {
    int z;
    cin>>z;
    cout<<(prime(z) ? "Prime":"Composite")<<endl;
    return 0;
}

