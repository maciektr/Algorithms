#include<bits/stdc++.h>
using namespace std;

struct node{
    int value;
    node *next;
    node(int v, node *n):value(v),next(n){}
};

void printList(node *head);
int countToEnd(node *head);
void getInput(node *&head);

node* takeLesser(node *&first, node *&second){
    auto takeFrom = [](node *&head){
        node * res = head;
        head = head->next;
        return res;
    };
    if(first!=nullptr && second!=nullptr){
        if(first->value < second->value)
            return takeFrom(first);  
        return takeFrom(second);
    }
    if(first==nullptr)
        return takeFrom(second);
    return takeFrom(first);
}

void mergeSortList(node *&head){
    int s = countToEnd(head)/2;
    if(s==0)
        return ;
    node *iter = head;
    int count = 0;
    while(iter!=nullptr && count<s-1){
        iter = iter->next;
        count++;
    }
    node *last = iter;
    iter = iter->next;
    last->next = nullptr;
    mergeSortList(head);
    mergeSortList(iter);
    node *list = takeLesser(iter,head);
    node *result = list;
    while(head != nullptr || iter != nullptr){
        list->next=takeLesser(iter,head);
        list=list->next;
    }
    head = result;
}

int main(){
    node *head=nullptr;
    getInput(head);
    mergeSortList(head);
    printList(head);
}

void getInput(node *&head){
    int n;
    cin>>n;
    while(n--){
        int tmp;
        cin>>tmp;
        head = new node(tmp,head);
    }
}

void printList(node *head){
    while(head!=nullptr){
        cout<<head->value<<(head->next==nullptr ? "\n":" ");
        head=head->next;
    }
}

int countToEnd(node *head){
    int result = 0; 
    while(head!=nullptr){
        result++;
        head=head->next;
    }
    return result;
}
