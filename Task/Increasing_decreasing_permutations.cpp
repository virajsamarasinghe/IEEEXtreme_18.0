#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

struct H {
    size_t operator()(const vector<int>& v) const {
        size_t h = 0;
        for (int x : v) {
            h ^= h * 31 + x;
        }
        return h;
    }
};

unordered_set<vector<int>, H> g(int n) {
    int m = (n + 1) / 2;
    unordered_set<vector<int>, H> s;
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);

    do {
        bool valid = true;
        for (int i = 0; i < m - 1; i++) {
            if (v[i] >= v[i + 1]) {
                valid = false;
                break;
            }
        }
        for (int i = m - 1; i < n - 1 && valid; i++) {
            if (v[i] <= v[i + 1]) {
                valid = false;
                break;
            }
        }
        if (valid) {
            s.insert(v);
        }
    } while (next_permutation(v.begin(), v.end()));

    return s;
}

unordered_map<vector<int>, int, H> m(const unordered_set<vector<int>, H>& s, int n) {
    unordered_map<vector<int>, int, H> m;
    queue<pair<vector<int>, int>> q;

    for (const auto& seq : s) {
        q.push({seq, 0});
        m[seq] = 0;
    }

    while (!q.empty()) {
        auto [cur, cnt] = q.front();
        q.pop();

        for (int i = 0; i < n - 1; i++) {
            vector<int> nxt = cur;
            swap(nxt[i], nxt[i + 1]);

            if (m.find(nxt) == m.end()) {
                m[nxt] = cnt + 1;
                q.push({nxt, cnt + 1});
            }
        }
    }

    return m;
}

int s(int n, int mod) {
    auto seqs = g(n);
    auto swaps = m(seqs, n);

    vector<int> v(n);
    iota(v.begin(), v.end(), 1);

    int t = 0;
    do {
        t = (t + swaps[v]) % mod;
    } while (next_permutation(v.begin(), v.end()));

    return t;
}

int main() {
    int n, mod;
    cin >> n >> mod;
    cout << s(n, mod) << endl;
    return 0;
}
