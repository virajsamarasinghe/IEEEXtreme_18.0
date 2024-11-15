//Task Score: 28%
//Did you do more than us committe to it in this repo
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long computeHilbertOrder(int x, int y) {
    long long hilbertOrder = 0;
    int bits = 32;

    for (int s = bits - 1; s >= 0; s--) {
        int bitX = (x >> s) & 1;
        int bitY = (y >> s) & 1;
        hilbertOrder += (1LL << (2 * s)) * ((3 * bitX) ^ bitY);

        if (bitY == 0) {
            if (bitX == 1) {
                x = (1 << (s + 1)) - 1 - x;
                y = (1 << (s + 1)) - 1 - y;
            }
            swap(x, y);
        }
    }
    return hilbertOrder;
}

int main() {
    int numPoints;
    cin >> numPoints;
    
    vector<pair<int, int>> points(numPoints);
    vector<long long> hilbertOrders(numPoints);
    vector<int> sortedIndices(numPoints);
    
    for (int i = 0; i < numPoints; i++) {
        int x, y;
        cin >> x >> y;
        
        int adjustedX = x + 2147483648LL;
        int adjustedY = y + 2147483648LL;
        
        hilbertOrders[i] = computeHilbertOrder(adjustedX, adjustedY);
        points[i] = {x, y};
        sortedIndices[i] = i;
    }

    sort(sortedIndices.begin(), sortedIndices.end(), [&](int a, int b) {
        return hilbertOrders[a] < hilbertOrders[b];
    });

    for (size_t i = 0; i < sortedIndices.size(); i += 3) {
        for (size_t j = 0; j < 3 && (i + j) < sortedIndices.size(); ++j) {
            cout << sortedIndices[i + j] << " ";
        }
        cout << endl;
    }

    return 0;
}
