#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
using namespace std;
using ll = long long;

class Solution {
    int N;
    vector<ll> sal;
    vector<int> hap;
    
    ll gcd(ll a, ll b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }
    
    pair<ll, ll> simplifyFraction(ll num, ll den) {
        ll g = gcd(abs(num), abs(den));
        return {num/g, den/g};
    }
    
public:
    Solution(int n, vector<ll>& init_sal) : N(n) {
        sal = init_sal;
        hap.resize(N, 0);
    }
    
    void setSalary(int l, int r, ll c) {
        for(int i = l-1; i < r; i++) {
            ll old_sal = sal[i];
            sal[i] = c;
            if(old_sal < c) hap[i]++;
            else if(old_sal > c) hap[i]--;
        }
    }
    
    void changeSalary(int l, int r, ll c) {
        for(int i = l-1; i < r; i++) {
            ll old_sal = sal[i];
            sal[i] += c;
            if(c > 0) hap[i]++;
            else if(c < 0) hap[i]--;
        }
    }
    
    pair<ll, ll> querySalary(int l, int r) {
        ll sum = 0;
        for(int i = l-1; i < r; i++) {
            sum += sal[i];
        }
        return simplifyFraction(sum, r-l+1);
    }
    
    pair<ll, ll> queryHappiness(int l, int r) {
        ll sum = 0;
        for(int i = l-1; i < r; i++) {
            sum += hap[i];
        }
        return simplifyFraction(sum, r-l+1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    cin >> N >> Q;
    
    vector<ll> init_sal(N);
    for(int i = 0; i < N; i++) {
        cin >> init_sal[i];
    }
    
    Solution sol(N, init_sal);
    
    while(Q--) {
        int type, l, r;
        cin >> type >> l >> r;
        
        if(type <= 1) {
            ll c;
            cin >> c;
            if(type == 0) sol.setSalary(l, r, c);
            else sol.changeSalary(l, r, c);
        } else {
            auto res = (type == 2) ? sol.querySalary(l, r) : sol.queryHappiness(l, r);
            cout << res.first << "/" << res.second << "\n";
        }
    }
    
    return 0;
}
