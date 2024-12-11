#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

ll max_after_swaps(ll n, int s) {
    string num = to_string(n);
    int len = num.length();
    
    if (s == 0) return n;
    
    for (int i = 0; i < len; i++) {
        char cur_digit = num[i];
        char max_digit = *max_element(num.begin() + i, num.end());
        
        if (max_digit > cur_digit) {
            vector<int> max_positions;
            for (int j = len - 1; j >= i; j--) {
                if (num[j] == max_digit) {
                    max_positions.push_back(j);
                }
            }
            
            ll max_res = n;
            for (int pos : max_positions) {
                string new_num = num;
                swap(new_num[i], new_num[pos]);
                
                int rem_swaps = s - 1;
                if (rem_swaps > 0) {
                    ll res = max_after_swaps(stoll(new_num), rem_swaps);
                    max_res = max(max_res, res);
                } else {
                    max_res = max(max_res, stoll(new_num));
                }
            }
            return max_res;
        }
    }
    
    return n;
}

int main() {
    ll n;
    int s;
    cin >> n >> s;
    
    ll result = max_after_swaps(n, s);
    cout << result << endl;

    return 0;
}
