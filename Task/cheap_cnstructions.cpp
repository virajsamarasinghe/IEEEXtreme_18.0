#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

typedef long long ll;

const int PB1 = 911, PB2 = 3571, M1 = 1000000007, M2 = 1000000009;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;
    int n = s.length();

    vector<int> h1(n + 1, 0), h2(n + 1, 0);
    vector<ll> p1(n + 1, 1), p2(n + 1, 1);

    for (int i = 0; i < n; i++) {
        h1[i + 1] = (1LL * h1[i] * PB1 + (s[i] - 'a' + 1)) % M1;
        h2[i + 1] = (1LL * h2[i] * PB2 + (s[i] - 'a' + 1)) % M2;
        if (i < n - 1) {
            p1[i + 1] = (p1[i] * PB1) % M1;
            p2[i + 1] = (p2[i] * PB2) % M2;
        }
    }

    vector<ll> maxP(n + 1, 1);
    for (int len = 1; len <= n; len++) {
        if (maxP[len - 1] <= 1e12 / 26) {
            maxP[len] = maxP[len - 1] * 26;
        } else {
            maxP[len] = 1e12;
        }
    }

    vector<int> minLen(n + 1, INT32_MAX);

    for (int len = 1; len <= n; len++) {
        vector<pair<ll, int>> hashes;
        hashes.reserve(n - len + 1);
        for (int i = 0; i <= n - len; i++) {
            ll h1_val = (h1[i + len] - (1LL * h1[i] * p1[len]) % M1 + M1) % M1;
            ll h2_val = (h2[i + len] - (1LL * h2[i] * p2[len]) % M2 + M2) % M2;
            ll combined = (h1_val << 32) | h2_val;
            hashes.emplace_back(combined, i);
        }

        sort(hashes.begin(), hashes.end());

        int uniqueCount = 0, total = hashes.size(), idx = 0;
        while (idx < total) {
            ll currHash = hashes[idx].first;
            int nextIdx = idx;
            while (nextIdx < total && hashes[nextIdx].first == currHash) {
                nextIdx++;
            }
            int groupSize = nextIdx - idx;
            uniqueCount++;

            vector<int> startPos;
            startPos.reserve(groupSize);
            for (int j = idx; j < nextIdx; j++) {
                startPos.push_back(hashes[j].second);
            }
            sort(startPos.begin(), startPos.end());

            int coverage = 0, lastEnd = -1;
            for (auto &start : startPos) {
                int end = start + len - 1;
                if (start > lastEnd) {
                    coverage += (end - start);
                } else {
                    coverage += max(0, end - lastEnd);
                }
                lastEnd = max(lastEnd, end);
            }

            int rem = n - coverage;
            if (rem >= 1 && rem <= n) {
                minLen[rem] = min(minLen[rem], len);
            }
            idx = nextIdx;
        }

        if (uniqueCount < maxP[len]) {
            minLen[n] = min(minLen[n], len);
        }
    }

    for (int k = 1; k <= n; k++) {
        if (minLen[k] == INT32_MAX) {
            minLen[k] = 0;
        }
    }

    for (int k = 1; k <= n; k++) {
        cout << minLen[k] << (k == n ? '\n' : ' ');
    }
}
