//Task Score: 33%
//Did you do more than us committe to it in this repo

#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
    }

    vector<long long> arr(n + 1, 0);

    for (int i = 0; i < q; i++) {
        int type;
        scanf("%d", &type);

        if (type == 0) {
            int l, r, c;
            scanf("%d %d %d", &l, &r, &c);
            for (int j = l; j <= r; j++) {
                arr[j] += c;
            }
        } else if (type == 1) {
            int l, r, c;
            scanf("%d %d %d", &l, &r, &c);
            for (int j = l; j <= r; j++) {
                arr[p[j]] += c;
            }
        } else if (type == 2) {
            int l, r;
            scanf("%d %d", &l, &r);
            long long sum = 0;
            for (int j = l; j <= r; j++) {
                sum += arr[j];
            }
            printf("%lld\n", sum);
        } else { // type == 3
            int l, r;
            scanf("%d %d", &l, &r);
            long long sum = 0;
            for (int j = l; j <= r; j++) {
                sum += arr[p[j]];
            }
            printf("%lld\n", sum);
        }
    }

    return 0;
}
