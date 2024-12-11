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

    vector<long long> a(n + 1, 0);

    for (int i = 0; i < q; i++) {
        int t;
        scanf("%d", &t);

        if (t == 0) {
            int l, r, c;
            scanf("%d %d %d", &l, &r, &c);
            for (int j = l; j <= r; j++) {
                a[j] += c;
            }
        } else if (t == 1) {
            int l, r, c;
            scanf("%d %d %d", &l, &r, &c);
            for (int j = l; j <= r; j++) {
                a[p[j]] += c;
            }
        } else if (t == 2) {
            int l, r;
            scanf("%d %d", &l, &r);
            long long s = 0;
            for (int j = l; j <= r; j++) {
                s += a[j];
            }
            printf("%lld\n", s);
        } else { // t == 3
            int l, r;
            scanf("%d %d", &l, &r);
            long long s = 0;
            for (int j = l; j <= r; j++) {
                s += a[p[j]];
            }
            printf("%lld\n", s);
        }
    }

    return 0;
}
