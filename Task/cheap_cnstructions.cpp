#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int PRIME_BASE1 = 911;
const int PRIME_BASE2 = 3571;
const int MOD1 = 1000000007;
const int MOD2 = 1000000009;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string input;
    cin >> input;
    int inputSize = input.length();

    vector<int> hashPrefix1(inputSize + 1, 0);
    vector<int> hashPrefix2(inputSize + 1, 0);
    vector<ll> powerBase1Values(inputSize + 1, 1);
    vector<ll> powerBase2Values(inputSize + 1, 1);

    for (int i = 0; i < inputSize; i++) {
        hashPrefix1[i + 1] = (1LL * hashPrefix1[i] * PRIME_BASE1 + (input[i] - 'a' + 1)) % MOD1;
        hashPrefix2[i + 1] = (1LL * hashPrefix2[i] * PRIME_BASE2 + (input[i] - 'a' + 1)) % MOD2;
        if (i < inputSize - 1) {
            powerBase1Values[i + 1] = (powerBase1Values[i] * PRIME_BASE1) % MOD1;
            powerBase2Values[i + 1] = (powerBase2Values[i] * PRIME_BASE2) % MOD2;
        }
    }

    vector<ll> maxPower26(inputSize + 1, 1);
    for (int length = 1; length <= inputSize; length++) {
        if (maxPower26[length - 1] <= 1e12 / 26) {
            maxPower26[length] = maxPower26[length - 1] * 26;
        } else {
            maxPower26[length] = 1e12;
        }
    }

    vector<int> minSubLen(inputSize + 1, INT32_MAX);

    for (int length = 1; length <= inputSize; length++) {
        vector<pair<ll, int>> hashGroups;
        hashGroups.reserve(inputSize - length + 1);
        for (int i = 0; i <= inputSize - length; i++) {
            ll subHash1 = (hashPrefix1[i + length] - (1LL * hashPrefix1[i] * powerBase1Values[length]) % MOD1 + MOD1) % MOD1;
            ll subHash2 = (hashPrefix2[i + length] - (1LL * hashPrefix2[i] * powerBase2Values[length]) % MOD2 + MOD2) % MOD2;
            ll combinedHash = (subHash1 << 32) | subHash2;
            hashGroups.emplace_back(combinedHash, i);
        }

        sort(hashGroups.begin(), hashGroups.end());

        int uniqueGroupCount = 0;
        int groupTotal = hashGroups.size();
        int idx = 0;

        while (idx < groupTotal) {
            ll currentHash = hashGroups[idx].first;
            int nextIdx = idx;
            while (nextIdx < groupTotal && hashGroups[nextIdx].first == currentHash) {
                nextIdx++;
            }
            int groupSize = nextIdx - idx;
            uniqueGroupCount++;

            vector<int> startPos;
            startPos.reserve(groupSize);
            for (int j = idx; j < nextIdx; j++) {
                startPos.push_back(hashGroups[j].second);
            }
            sort(startPos.begin(), startPos.end());

            int coverage = 0;
            int lastEnd = -1;
            for (auto &start : startPos) {
                int end = start + length - 1;
                if (start > lastEnd) {
                    coverage += (end - start);
                } else {
                    coverage += max(0, end - lastEnd);
                }
                lastEnd = max(lastEnd, end);
            }

            int remainingChars = inputSize - coverage;
            if (remainingChars >= 1 && remainingChars <= inputSize) {
                minSubLen[remainingChars] = min(minSubLen[remainingChars], length);
            }
            idx = nextIdx;
        }

        if (uniqueGroupCount < maxPower26[length]) {
            minSubLen[inputSize] = min(minSubLen[inputSize], length);
        }
    }

    for (int k = 1; k <= inputSize; k++) {
        if (minSubLen[k] == INT32_MAX) {
            minSubLen[k] = 0;
        }
    }

    for (int k = 1; k <= inputSize; k++) {
        cout << minSubLen[k] << (k == inputSize ? '\n' : ' ');
    }
}

//100% marks