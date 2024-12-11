#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long calcValidSum(const vector<int>& a, int maxSum) {
    int n = a.size();
    long long totalSum = 0;
    
    for (int s = 0; s < n; s++) {
        int e = s;
        while (e < n) {
            int len = e - s + 1;
            bool valid = true;

            if (len % 2 == 0) {
                int maxPair = 0;
                for (int i = 0; i < len / 2; i++) {
                    maxPair = max(maxPair, a[s + i] + a[e - i]);
                }
                valid = maxPair <= maxSum;
            } else {
                int maxElem = a[e];
                int maxPair = 0;
                for (int i = 0; i < (len - 1) / 2; i++) {
                    maxPair = max(maxPair, a[s + i] + a[e - 1 - i]);
                }
                valid = max(maxElem, maxPair) <= maxSum;
            }

            if (!valid) break;

            totalSum += a[e] - a[s];
            e++;
        }
    }
    return totalSum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    while (q--) {
        int maxSum;
        cin >> maxSum;
        cout << calcValidSum(a, maxSum) << '\n';
    }
    
    return 0;
}
