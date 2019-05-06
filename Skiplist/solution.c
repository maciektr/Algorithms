#define MAX_LEVEL 32 

#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<limits.h>
typedef struct SLNode SLNode;
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

struct SLNode{
    int key;
    SLNode **next;
};

typedef struct SkipList{
    SLNode *first;
    SLNode *last;
    int maxLevel; //Given to first and last
} SkipList;

int getLevel(void);
void initSkipList(SkipList *sl);
void deleteSkipList(SkipList *sl);

void print(SkipList *sl){
    SLNode *p = sl->first;
    p = p->next[0];
    while(p!=sl->last){
        printf("%d ",p->key);
        p = p->next[0];
    }
    printf("\n");
}

void insert(SkipList *sl, int key){
    SLNode *p = sl->first;
    int level = sl->maxLevel;

    SLNode *newNode = (SLNode *)malloc(sizeof(SLNode));
    newNode->key = key;
    int newLevel = getLevel();
    newNode->next = (SLNode **)malloc((newLevel+1)* sizeof(SLNode *));

    while(level-- >0){
        while(p->next[level]!=sl->last && p->next[level]->key < newNode->key)
            p = p->next[level];
        if(level <= newLevel){
            SLNode *tmp = p->next[level];
            p->next[level] = newNode; 
            newNode->next[level] = tmp;          
        }
        
    }
}

SLNode *find(SkipList *sl, int key){
    SLNode *p = sl->first;
    int level = sl->maxLevel;

    while(level-- > 0){
        while(p->next[level]!=sl->last && p->next[level]->key <= key)
            p = p->next[level];
    }

    return (p->key == key ? p:NULL);
}

void removeElement(SkipList *sl, int key){
    SLNode *r = find(sl,key);
    if(r==NULL)
        return;

    SLNode *p = sl->first;
    int level = sl->maxLevel;
    
    while(level-- >0){
        while(p->next[level]!=sl->last && p->next[level]->key < key)
            p = p->next[level];
        if(p->next[level]==r)
            p->next[level] = r->next[level];
    }
    free(r->value);
    free(r->next);
    free(r);
}

void solve(SkipList *sl){
    //for testing purpose 
    int n;
    scanf("%d",&n);
    while(n-->0){
        char *rtmp = (char *)malloc(sizeof(char)*2);
        rtmp[0]=rtmp[1]='\0';
        scanf("%s",rtmp);
        char tmp = rtmp[0];
        free(rtmp);

        if(tmp=='p')
            print(sl);
        else{
            int v; 
            scanf("%d",&v);
            if(tmp=='i')
                insert(sl,v);
            else if(tmp=='r')
                removeElement(sl,v);
            else if(tmp=='f'){
                SLNode *k = find(sl,v);
                if(k!=NULL)
                    printf("%d\n",k->key);
                else 
                    printf("None\n");
            }
        }
    }
}

int main(){
    srand(time(0));
    SkipList *sl = (SkipList *)malloc(sizeof(SkipList));
    initSkipList(sl);
    solve(sl);
    deleteSkipList(sl);
    return 0;
} 

int getLevel(void){
   return max(1,min(__builtin_ffs(rand()),MAX_LEVEL));
}

void initSkipList(SkipList *sl){
    sl->maxLevel = MAX_LEVEL;    
    sl->first = (SLNode *)malloc(sizeof(SLNode));
    sl->last = (SLNode *)malloc(sizeof(SLNode));
    sl->first->key = -1*(INT_MAX-3);
    sl->last->key = INT_MAX-3;
    sl->first->next = (SLNode **)malloc((sl->maxLevel+1)*sizeof(SLNode *));
    sl->last->next = (SLNode **)malloc((sl->maxLevel+1)*sizeof(SLNode *));
    for(int i = 0; i<MAX_LEVEL; i++){
        sl->first->next[i] = sl->last;
        sl->last->next[i] = NULL;
    }
}

void deleteSkipList(SkipList *sl){
    SLNode *p = sl->first;
    while(p!=sl->last){
        SLNode *tmp = p;
        p = p->next[0];
        free(tmp->next);
        free(tmp);  
    }
    free(sl->last->next);
    free(sl->last);
    free(sl);
        
}
