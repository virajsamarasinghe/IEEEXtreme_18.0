#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MOD = 998244353;

int n;
vector<int> c, r, b;
map<pair<int, vector<int>>, int> memo;

int f(int p, vector<int>& rem) {
    if(p == n) return 1;
    
    pair<int, vector<int>> st = {p, rem};
    if(memo.count(st)) return memo[st];
    
    int res = 0;
    int p2 = 2 * p;
    
    vector<int> nums1;
    if(c[p2] != -1) nums1 = {c[p2]};
    else nums1 = rem;
    
    for(int n1 : nums1) {
        if(c[p2] != -1 && c[p2] != n1) continue;
        
        vector<int> nums2;
        if(c[p2 + 1] != -1) nums2 = {c[p2 + 1]};
        else {
            nums2 = rem;
            if(find(nums2.begin(), nums2.end(), n1) != nums2.end())
                nums2.erase(find(nums2.begin(), nums2.end(), n1));
        }
        
        for(int n2 : nums2) {
            if(c[p2 + 1] != -1 && c[p2 + 1] != n2) continue;
            if(n1 == n2) continue;
            
            int mn = min(n1, n2);
            int mx = max(n1, n2);
            
            if((r[p] == 0 && b[p] == mn) || (r[p] == 1 && b[p] == mx)) {
                vector<int> new_rem = rem;
                if(c[p2] == -1)
                    new_rem.erase(find(new_rem.begin(), new_rem.end(), n1));
                if(c[p2 + 1] == -1)
                    new_rem.erase(find(new_rem.begin(), new_rem.end(), n2));
                
                res = (res + f(p + 1, new_rem)) % MOD;
            }
        }
    }
    
    return memo[st] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    c.resize(2 * n);
    r.resize(n);
    b.resize(n);
    
    vector<int> rem;
    vector<bool> used(2 * n + 1, false);
    
    for(int i = 0; i < 2 * n; i++) {
        cin >> c[i];
        if(c[i] != -1) used[c[i]] = true;
    }
    
    for(int i = 1; i <= 2 * n; i++) {
        if(!used[i]) rem.push_back(i);
    }
    
    for(int i = 0; i < n; i++) cin >> r[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    
    cout << f(0, rem) << endl;
    
    return 0;
}
