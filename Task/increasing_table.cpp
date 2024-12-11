#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
using namespace std;

typedef long long ll;
const int M = 998244353;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    int X;
    cin >> X;
    vector<int> A(X);
    for (auto &x : A) cin >> x;
    int Y;
    cin >> Y;
    vector<int> B(Y);
    for (auto &x : B) cin >> x;

    vector<int> t(2 * N + 1, 0);
    for (auto x : A) t[x] = 1;
    for (auto x : B) t[x] = 2;

    vector<int> n;
    for (int i = 1; i <= 2 * N; i++) n.push_back(i);

    vector<ll> dp(N + 1, 0);
    dp[0] = 1;
    for (auto x : n) {
        vector<ll> dp_next(N + 1, 0);
        if (t[x] == 1) {
            for (int d = 0; d < N; d++) {
                dp_next[d + 1] = (dp_next[d + 1] + dp[d]) % M;
            }
        }
        else if (t[x] == 2) {
            for (int d = 1; d <= N; d++) {
                dp_next[d - 1] = (dp_next[d - 1] + dp[d]) % M;
            }
        }
        else {
            for (int d = 0; d < N; d++) {
                dp_next[d + 1] = (dp_next[d + 1] + dp[d]) % M;
            }

            for (int d = 1; d <= N; d++) {
                dp_next[d - 1] = (dp_next[d - 1] + dp[d]) % M;
            }
        }
        dp = dp_next;
    }
    cout << dp[0];
}
