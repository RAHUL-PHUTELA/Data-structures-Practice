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


int main(){
    int n = 8;
    // vector<int> dp(n+1, -1);
    // cout<<"fibnocci of "<<n<<" : "<<fib_rec(n)<< endl;
    // cout<<"fibnocci of "<<n<<" : "<<fib_memo(n, dp)<< endl;
    // cout<<"fibnocci of "<<n<<" : "<<fib_tabulation(n, dp)<< endl;
    cout<<"fibnocci of "<<n<<" : "<<fib_TwoPointer(n)<< endl;
}