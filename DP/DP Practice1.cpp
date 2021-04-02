// Questions 
// 1. Fibonacci Number - 12 - 59
// 2. Maze Path with Single Jump 87
// 3. Maze Path with Multi Jump 134
// 4.





#include<iostream>
#include<vector>

using namespace std;


// fibonacci-number
//509. Fibonacci Number
//https://leetcode.com/problems/fibonacci-number/
int fib_rec(int n){
    if(n<=1)
        return n;
    return fib_rec(n-1)+fib_rec(n-2);
}

int fib_memo(int n, vector<int>& dp){
    if(n<=1){
        return(dp[n] = n);
    }
    int a = dp[n-1];
    int b = dp[n-2];
    if(a == -1){
        a = fib_memo(n-1, dp);
    }
    if(b == -1){
        b = fib_memo(n-2, dp);
    }
    return(dp[n] = a + b);
}

int fib_tabulation(int N, vector<int>& dp){
    for(int n=0 ; n<=N;n++){
        if(n<=1){
            dp[n] = n;
            continue;
        }
        int a = dp[n-1];
        int b = dp[n-2];
        dp[n] = a + b;
    }
    return dp[N];
}

int fib_TwoPointer(int N){
    int a = 0, b = 1;
    if(N < 2){
        return N == 1 ? 1 : 0; 
    }
    
    int sum;
    for(int n=2 ; n<=N;n++){
        sum = a+b;
        a = b;
        b = sum;
    }
    return sum;
}

void Print1D(vector<int> arr){
    cout<<endl<<"Printing 1d: ";
    for(int a: arr){
        cout<<a<<" ";
    }
    cout<<endl;
}

void Print2D(vector<vector<int>> arr){
    cout<<endl<<"Printing 2d:\n";
    for(vector<int> a: arr){
        for(int b: a)
            cout<<b<<" ";
        cout<<endl;
    }
    cout<<endl;
}

// Maze Path with single Jump
int ThreeDirArr[3][2]= {
    {0,1},
    {1,1},
    {1,0}
};

int mazePathSingleJump(int r, int c, int n, int m, vector<vector<int>> &dp){
    if(r == n && c == m){
        return dp[n][m] = 1;
    }
    if(dp[r][c] != -1){
        return dp[r][c];
    }
    int count = 0;
    for(int i=0;i<3;i++){
        int x = r + ThreeDirArr[i][0];
        int y = c + ThreeDirArr[i][1];
        if(x>=0 && y>=0 && x<=n && y<=m){
            count += mazePathSingleJump(x, y, n, m, dp);
        }
    }
    return dp[r][c] = count;
}

int mazePathSingleJump_tabulation(int r, int c, int n, int m, vector<vector<int>> &dp){
    for(int r=n;r>=0;--r){
        for(int c=m;c>=0;--c){
            if(r == n && c == m){
                dp[n][m] = 1;
                continue;
            }
            int count = 0;
            for(int i=0;i<3;i++){
                int x = r + ThreeDirArr[i][0];
                int y = c + ThreeDirArr[i][1];
                if(x>=0 && y>=0 && x<=n && y<=m){
                    count += dp[x][y];
                }
            }
            dp[r][c] = count;    
        }
    }
    return dp[0][0];
}


// Maze Path with Multi Jump
int mazePathMultiJump(int r, int c, int n, int m, vector<vector<int>> &dp){
    if(r == n && c == m){
        return dp[n][m] = 1;
    }
    if(dp[r][c] != -1){
        return dp[r][c];
    }
    int count = 0;  
    for(int i=0;i<3;i++){
        for(int j=1;j<=max(n,m);j++){
            int x = r + j*ThreeDirArr[i][0];
            int y = c + j*ThreeDirArr[i][1];
            if(x>=0 && y>=0 && x<=n && y<=m){
                count += mazePathMultiJump(x, y, n, m, dp);
            }
        }
    }
    return dp[r][c] = count;
}

int mazePathMultiJump_tabulation(int R, int C, int n, int m, vector<vector<int>> &dp){
    for(int r = n; r>=0;--r){
        for(int c = m;c>=0;--c){
            if(r == n && c == m){
                dp[n][m] = 1;
                continue;
            }
            int count = 0;  
            for(int i=0;i<3;i++){
                for(int j=1;j<=max(n,m);j++){
                    int x = r + j*ThreeDirArr[i][0];
                    int y = c + j*ThreeDirArr[i][1];
                    if(x>=0 && y>=0 && x<=n && y<=m){
                        count += mazePathMultiJump(x, y, n, m, dp);
                    }
                }
            }
            dp[r][c] = count;        
        }
    }
    return dp[0][0];
}

int DiceProblem_memo(int a, int Start, int End, int TarB, vector<int> &dp){
    if(a == TarB){
        return dp[a] = 1;
    }
    int c = 0;
    if(dp[a] != -1){
        return dp[a];
    }
    for(int i=Start;i<=End ; i++){
        if(a + i <=TarB){
            c+=DiceProblem_memo(a + i, Start, End, TarB, dp);
        }
    }
    return dp[a] = c;
}


int DiceProblem_tabulation(int a, int Start, int End, int TarB, vector<int> &dp){
    for(int a=TarB;a>=0;--a){
        if(a == TarB){
            dp[a] = 1;
            continue;
        }
        int c = 0;
        for(int i=Start;i<=End ; i++){
            if(a + i <=TarB){
                c+=dp[a+i];
            }
        }
        dp[a] = c;
    }
    return(dp[0]);
}

struct Node{
    int data;
    Node *Pre;
    Node *next;
};

struct DLL{
    Node *head;
    Node *tail;
};

DLL* AddFirst(DLL *DLL,int data){
    Node* newNode = new Node;
    newNode->data = data;
    newNode->Pre = NULL;
    newNode->next = NULL;
    if(DLL->head == NULL){
        DLL->head = newNode;
        DLL->tail = newNode;
        return DLL;
    }
    newNode->next = DLL->head;
    DLL->head->Pre = newNode;
    DLL->head = newNode;
    return DLL;
}

DLL* RemoveLast(DLL *DLL){
    DLL->tail = DLL->tail->Pre;
    DLL->tail->next = NULL;
    return DLL;
}


int DiceProblem_Optimized(int a, int Start, int End, int TarB){
    DLL *dll = new DLL;
    dll->head = NULL;
    dll->tail = NULL;
    dll = AddFirst(dll, 1);
    dll = AddFirst(dll, 1);
    for(int i=0;i<5 && i<TarB;i++){
        dll = AddFirst(dll, dll->head->data*2);
    }
    TarB = TarB - 7;
    for(int i=0;i<=TarB;i++){
        dll = AddFirst(dll, dll->head->data*2 - dll->tail->data);
        dll = RemoveLast(dll);
    }
    cout<<"\nDisplaying List: ";
    Node *head = dll->head;
    while(head != NULL){
        cout<<head->data<<" ";
        head = head->next;
    }
    cout<<endl;
    return dll->head->data;
}

// Dice Problem with given Array
int DiceProblemWithArray_memo(int a,int MoveArray[], int End, int TarB, vector<int> &dp){
    if(a == TarB){
        return dp[a] = 1;
    }
    int c = 0;
    if(dp[a] != -1){
        return dp[a];
    }
    for(int i=0;i<End ; i++){
        if(a + MoveArray[i] <=TarB){
            c+=DiceProblemWithArray_memo(a + MoveArray[i], MoveArray, End, TarB, dp);
        }
    }
    return dp[a] = c;
}

int DiceProblemWithArray_tabulation(int a,int MoveArray[], int End, int TarB, vector<int> &dp){
    for(int a=TarB;a>=0;--a){
        if(a == TarB){
            dp[a] = 1;
            continue;
        }
        int c = 0;
        for(int i=0;i<End ; i++){
            if(a + MoveArray[i] <=TarB){
                c+=dp[a+MoveArray[i]];
            }
        }
        dp[a] = c;
    }
    return(dp[0]);
}

int main(){

    // Fibonacci Number
    // int n = 8;
    // vector<int> dp(n+1, -1);
    // cout<<"fibnocci of "<<n<<" : "<<fib_rec(n)<< endl;
    // cout<<"fibnocci of "<<n<<" : "<<fib_memo(n, dp)<< endl;
    // cout<<"fibnocci of "<<n<<" : "<<fib_tabulation(n, dp)<< endl;
    // cout<<"fibnocci of "<<n<<" : "<<fib_TwoPointer(n)<< endl;

    // Maze Path with single Jump
    // int n = 5,m = 5;
    // vector<vector<int>> dp(n, vector<int>(m, -1));
    // cout<<"Number of Paths: "<<mazePathSingleJump(0, 0, n-1, m-1, dp);
    // Print2D(dp);
    // vector<vector<int>> dp_2(n, vector<int>(m, -1));
    // cout<<"Number of Paths: "<<mazePathSingleJump_tabulation(0, 0, n-1, m-1, dp_2);
    // Print2D(dp_2);
    
    // Maze Path with Multi Jump
    // cout<<"Number of Paths: "<<mazePathMultiJump(0, 0, n-1, m-1, dp);
    // Print2D(dp);
    // cout<<"Number of Paths: "<<mazePathMultiJump_tabulation(0, 0, n-1, m-1, dp_2);
    // Print2D(dp_2);

    // Dice Problem
    int a = 0;
    int b = 10;
    int DiceStart = 1;
    int DiceEnd = 6;
    vector<int> dp(b-a+1, -1);
    cout<<"Number of Ways: "<<DiceProblem_memo(a, DiceStart, DiceEnd, b, dp);
    Print1D(dp);
    vector<int> dp_2(b-a+1, -1);
    cout<<"Number of Ways: "<<DiceProblem_tabulation(a, DiceStart, DiceEnd, b, dp_2);
    Print1D(dp_2);
    cout<<"Number of Ways: "<<DiceProblem_Optimized(a, DiceStart, DiceEnd, b);

    // Dice Probelm with given Array
    int MoveArray[4] = {2,3,5,8};
    vector<int> dp_4(b-a+1, -1);
    cout<<"\nNumber of Ways: "<<DiceProblemWithArray_memo(a, MoveArray, 4, b, dp_4);
    Print1D(dp_4);
    vector<int> dp_3(b-a+1, -1);
    cout<<"\nNumber of Ways: "<<DiceProblemWithArray_tabulation(a, MoveArray, 4, b, dp_3);
    Print1D(dp_3);
}