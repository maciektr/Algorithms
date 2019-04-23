#include<bits/stdc++.h>
using namespace std;

struct subset{
    int parent;
    int rank;
    subset()
        :parent(0),rank(0)
        {}
    subset(int p, int r)
        :parent(p),rank(r)
        {}
};

int getBoard(bool **&board);
subset *makeSets(bool **board, int n);
int set_find(int x, subset *sets);
void set_union(int x, int y, subset *sets);

void answer(void){
    
    bool **board;
    int n = getBoard(board);
    
    subset *sets = makeSets(board,n);
    auto set_id = [n](int a, int b){
        return a*n+b;
    };

    int *results = new int[n*n];
    for(int i = 0; i<n*n; i++)
        results[i] = 0;
        
    for(int i = 0; i<n; i++)
        for(int k = 0; k<n; k++)
            results[set_find(set_id(i,k), sets)]++;

    int k;
    cin>>k;
    while(k--){
        int x,y;
        cin>>x>>y;
        cout<<results[set_find(x*n+y,sets)]-1<<endl;
    }

    delete[](sets);
    delete[](results);
    for(int i = 0; i<n; i++)
        delete[](board[i]);
    delete[](board);

}

int main(){
    answer();
}

int set_find(int x, subset *sets){
    if(sets[x].parent==x)
        return x;
    sets[x].parent = set_find(sets[x].parent,sets);
    return sets[x].parent;
}

void set_union(int x, int y, subset *sets){
    x = set_find(x,sets);
    y = set_find(y,sets);
    if(sets[x].rank > sets[y].rank)   
        sets[y].parent = x;
    else 
        sets[x].parent = y;
    if(sets[x].rank == sets[y].rank)
        sets[y].rank++;
}

subset *makeSets(bool **board, int n){
    subset *sets = new subset[n*n];
    for(int i = 0; i<n*n; i++){
        sets[i].parent = i;
        sets[i].rank = 0;
    }
    
    auto set_id = [n](int a, int b){
        return a*n+b;
    };

    for(int x = 0; x<n; x++)
        for(int y = 0; y<n; y++){
            if(x+1<n && board[x][y] && board[x+1][y])
                set_union(set_id(x,y),set_id(x+1,y),sets);
            if(y+1<n && board[x][y] && board[x][y+1])
                set_union(set_id(x,y),set_id(x,y+1),sets);
        }

    return sets;
}

int getBoard(bool **&board){
    int n;
    cin>>n;
    board = new bool *[n];
    for(int i = 0; i<n; i++)
        board[i] = new bool[n];
    for(int i = 0; i<n; i++)
        for(int k = 0; k<n; k++){
            char tmp;
            cin>>tmp;
            board[i][k] = (tmp=='1');
        }
    return n;
}
