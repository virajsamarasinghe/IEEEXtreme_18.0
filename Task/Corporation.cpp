//Task Score: 30%
//Did you do more than us committe to it in this repo
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
using namespace std;
using ll = long long;

class Solution {
    int N;
    vector<ll> salary;
    vector<int> happiness;
    
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
    Solution(int n, vector<ll>& initial_salary) : N(n) {
        salary = initial_salary;
        happiness.resize(N, 0);
    }
    
    void setSalary(int l, int r, ll c) {
        for(int i = l-1; i < r; i++) {
            ll old_salary = salary[i];
            salary[i] = c;
            if(old_salary < c) happiness[i]++;
            else if(old_salary > c) happiness[i]--;
        }
    }
    
    void changeSalary(int l, int r, ll c) {
        for(int i = l-1; i < r; i++) {
            ll old_salary = salary[i];
            salary[i] += c;
            if(c > 0) happiness[i]++;
            else if(c < 0) happiness[i]--;
        }
    }
    
    pair<ll, ll> querySalary(int l, int r) {
        ll sum = 0;
        for(int i = l-1; i < r; i++) {
            sum += salary[i];
        }
        return simplifyFraction(sum, r-l+1);
    }
    
    pair<ll, ll> queryHappiness(int l, int r) {
        ll sum = 0;
        for(int i = l-1; i < r; i++) {
            sum += happiness[i];
        }
        return simplifyFraction(sum, r-l+1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    cin >> N >> Q;
    
    vector<ll> initial_salary(N);
    for(int i = 0; i < N; i++) {
        cin >> initial_salary[i];
    }
    
    Solution sol(N, initial_salary);
    
    while(Q--) {
        int type, l, r;
        cin >> type >> l >> r;
        
        if(type <= 1) {
            ll c;
            cin >> c;
            if(type == 0) sol.setSalary(l, r, c);
            else sol.changeSalary(l, r, c);
        } else {
            auto result = (type == 2) ? sol.querySalary(l, r) : sol.queryHappiness(l, r);
            cout << result.first << "/" << result.second << "\n";
        }
    }
    
    return 0;
}
