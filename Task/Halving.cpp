//Task Score: 30%
//Did you do more than us committe to it in this repo
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MOD = 998244353;

int n;
vector<int> c, r, b;
map<pair<int, vector<int>>, int> memo;

int solve(int pos, vector<int>& remaining) {
    if(pos == n) return 1;
    
    pair<int, vector<int>> state = {pos, remaining};
    if(memo.count(state)) return memo[state];
    
    int result = 0;
    int pos2 = 2 * pos;
    
    // Get available numbers for first position
    vector<int> nums1;
    if(c[pos2] != -1) nums1 = {c[pos2]};
    else nums1 = remaining;
    
    for(int num1 : nums1) {
        if(c[pos2] != -1 && c[pos2] != num1) continue;
        
        // Get available numbers for second position
        vector<int> nums2;
        if(c[pos2 + 1] != -1) nums2 = {c[pos2 + 1]};
        else {
            nums2 = remaining;
            if(find(nums2.begin(), nums2.end(), num1) != nums2.end())
                nums2.erase(find(nums2.begin(), nums2.end(), num1));
        }
        
        for(int num2 : nums2) {
            if(c[pos2 + 1] != -1 && c[pos2 + 1] != num2) continue;
            if(num1 == num2) continue;
            
            int mn = min(num1, num2);
            int mx = max(num1, num2);
            
            if((r[pos] == 0 && b[pos] == mn) || (r[pos] == 1 && b[pos] == mx)) {
                vector<int> new_remaining = remaining;
                if(c[pos2] == -1)
                    new_remaining.erase(find(new_remaining.begin(), new_remaining.end(), num1));
                if(c[pos2 + 1] == -1)
                    new_remaining.erase(find(new_remaining.begin(), new_remaining.end(), num2));
                
                result = (result + solve(pos + 1, new_remaining)) % MOD;
            }
        }
    }
    
    return memo[state] = result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    c.resize(2 * n);
    r.resize(n);
    b.resize(n);
    
    vector<int> remaining;
    vector<bool> used(2 * n + 1, false);
    
    for(int i = 0; i < 2 * n; i++) {
        cin >> c[i];
        if(c[i] != -1) used[c[i]] = true;
    }
    
    for(int i = 1; i <= 2 * n; i++) {
        if(!used[i]) remaining.push_back(i);
    }
    
    for(int i = 0; i < n; i++) cin >> r[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    
    cout << solve(0, remaining) << endl;
    
    return 0;
}