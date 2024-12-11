import sys
import threading

def main():
    sys.setrecursionlimit(1 << 25)
    N = int(sys.stdin.readline())
    w = [0] + list(map(int, sys.stdin.readline().split()))
    e = [[] for _ in range(N + 1)]
    
    for _ in range(N - 1):
        u, v = map(int, sys.stdin.readline().split())
        e[u].append(v)
        e[v].append(u)

    MOD = 10 ** 9 + 99999

    maxN = N
    f = [1] * (maxN + 1)
    i_f = [1] * (maxN + 1)
    inv = [1] * (maxN + 1)
    
    for i in range(2, maxN + 1):
        f[i] = f[i - 1] * i % MOD
        inv[i] = MOD - MOD // i * inv[MOD % i] % MOD
        i_f[i] = i_f[i - 1] * inv[i] % MOD

    def C(n, k):
        if n < k or k < 0:
            return 0
        return f[n] * i_f[k] % MOD * i_f[n - k] % MOD

    sz = [0] * (N + 1)

    def dfs(u, p):
        sz[u] = 1
        for v in e[u]:
            if v != p:
                dfs(v, u)
                sz[u] += sz[v]
        return sz[u]

    dfs(1, -1)

    T_C = [0] * (N + 1)
    for k in range(N + 1):
        T_C[k] = C(N, k)

    res = [0] * N

    for k in range(1, N + 1):
        total = 0
        for v in range(1, N + 1):
            ex = 0
            for c in e[v]:
                if sz[c] < sz[v]:
                    ex = (ex + C(sz[c], k)) % MOD
            ex = (ex + C(N - sz[v], k)) % MOD
            inc = (T_C[k] - ex + MOD) % MOD
            total = (total + w[v] * inc) % MOD
        res[k - 1] = total

    for r in res:
        print(r)

threading.Thread(target=main).start()
