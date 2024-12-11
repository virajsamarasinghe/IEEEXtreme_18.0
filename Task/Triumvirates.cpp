#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long hilbertOrder(int x, int y) {
    long long order = 0;
    int bits = 32;

    for (int s = bits - 1; s >= 0; s--) {
        int bx = (x >> s) & 1;
        int by = (y >> s) & 1;
        order += (1LL << (2 * s)) * ((3 * bx) ^ by);

        if (by == 0) {
            if (bx == 1) {
                x = (1 << (s + 1)) - 1 - x;
                y = (1 << (s + 1)) - 1 - y;
            }
            swap(x, y);
        }
    }
    return order;
}

int main() {
    int n;
    cin >> n;
    
    vector<pair<int, int>> pts(n);
    vector<long long> orders(n);
    vector<int> indices(n);
    
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        
        int adjX = x + 2147483648LL;
        int adjY = y + 2147483648LL;
        
        orders[i] = hilbertOrder(adjX, adjY);
        pts[i] = {x, y};
        indices[i] = i;
    }

    sort(indices.begin(), indices.end(), [&](int a, int b) {
        return orders[a] < orders[b];
    });

    for (size_t i = 0; i < indices.size(); i += 3) {
        for (size_t j = 0; j < 3 && (i + j) < indices.size(); ++j) {
            cout << indices[i + j] << " ";
        }
        cout << endl;
    }

    return 0;
}
