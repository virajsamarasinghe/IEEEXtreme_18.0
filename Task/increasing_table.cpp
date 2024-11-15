#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD=998244353;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin>>N;
    int X;
    cin>>X;
    vector<int> A(X);
    for(auto &x:A) cin>>x;
    int Y;
    cin>>Y;
    vector<int> B(Y);
    for(auto &x:B) cin>>x;
    
    vector<int> type(2*N+1,0);
    for(auto x:A) type[x]=1;
    for(auto x:B) type[x]=2;
    
    vector<int> numbers;
    for(int i=1;i<=2*N;i++) numbers.push_back(i);
   
    vector<ll> dp(N+1,0);
    dp[0]=1;
    for(auto x:numbers){
        vector<ll> dp_next(N+1,0);
        if(type[x]==1){
            for(int d=0; d<N; d++) {
                dp_next[d+1] = (dp_next[d+1] + dp[d])%MOD;
            }
        }
        else if(type[x]==2){
            for(int d=1; d<=N; d++) {
                dp_next[d-1] = (dp_next[d-1] + dp[d])%MOD;
            }
        }
        else{
           
            for(int d=0; d<N; d++) {
                dp_next[d+1] = (dp_next[d+1] + dp[d])%MOD;
            }
            
            for(int d=1; d<=N; d++) {
                dp_next[d-1] = (dp_next[d-1] + dp[d])%MOD;
            }
        }
        dp = dp_next;
    }
    cout<<dp[0];
}
//100% marks