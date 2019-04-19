#include<bits/stdc++.h>
using namespace std;
int getInput(int *&tab);

int select(int tab[],int n, int k){
    if(n<=7){
        sort(tab, tab+n);
        return tab[k];
    }

    int *medians = new int[n/5+1];
    for(int i = 0; i<n; i+=5){
        sort(tab+i,tab+i+min(5,n-i));
        medians[i/5] = tab[i+min(2,(n-i)/2)];
    }
    int m = select(medians,n/5+1,(n/5+1)/2);
    delete[] medians;

    int *lesser = new int[n];
    int *equal = new int[n];
    int *greater = new int[n];
    int greaterIndex = 0;
    int lesserIndex = 0;
    int equalIndex = 0;

    for(int i = 0; i<n; i++)
        if(tab[i] < m)
            lesser[lesserIndex++]=tab[i];
        else if(tab[i] == m)
            equal[equalIndex++]=tab[i];
        else
            greater[greaterIndex++]=tab[i];

    if(lesserIndex>k){
        int res = select(lesser,lesserIndex,k);
        delete[] greater;
        delete[] equal;
        delete[] lesser;

        return res;
    }
    else if(lesserIndex+equalIndex>k){
        delete[] lesser;
        delete[] equal;
        delete[] greater;

        return m;
    }
    int res =  select(greater,greaterIndex,k-lesserIndex-equalIndex);

    delete[] lesser;
    delete[] equal;
    delete[] greater;
    return res;
    
}

int main(){
    ios_base::sync_with_stdio(0);
    int *tab=NULL;
    int n = getInput(tab);
    int k;
    cin>>k;
    cout<<select(tab,n,k)<<endl;
    delete[] tab;
}

int getInput(int *&tab){
    int n;
    cin>>n; 
    tab = new int[n];
    for(int i = 0; i<n; i++)
        cin>>tab[i];
    return n;
}
