import sys
import threading

def main():
    import sys
    sys.setrecursionlimit(1 << 25)
    N = int(sys.stdin.readline())
    weights = [0] + list(map(int, sys.stdin.readline().split()))
    edges = [[] for _ in range(N + 1)]
    for _ in range(N - 1):
        u, v = map(int, sys.stdin.readline().split())
        edges[u].append(v)
        edges[v].append(u)

    MOD = 10 ** 9 + 99999

    # Precompute factorials and inverse factorials
    maxN = N
    fac = [1] * (maxN + 1)
    ifac = [1] * (maxN + 1)
    inv = [1] * (maxN + 1)
    for i in range(2, maxN + 1):
        fac[i] = fac[i - 1] * i % MOD
        inv[i] = MOD - MOD // i * inv[MOD % i] % MOD
        ifac[i] = ifac[i - 1] * inv[i] % MOD

    def C(n, k):
        if n < k or k < 0:
            return 0
        return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD

    size = [0] * (N + 1)

    def dfs(u, p):
        size[u] = 1
        for v in edges[u]:
            if v != p:
                dfs(v, u)
                size[u] += size[v]
        return size[u]

    dfs(1, -1)

    total_C = [0] * (N + 1)
    for k in range(N + 1):
        total_C[k] = C(N, k)

    result = [0] * N

    for k in range(1, N + 1):
        total = 0
        for v in range(1, N + 1):
            exclude = 0
            for c in edges[v]:
                if size[c] < size[v]:
                    exclude = (exclude + C(size[c], k)) % MOD
            exclude = (exclude + C(N - size[v], k)) % MOD
            include = (total_C[k] - exclude + MOD) % MOD
            total = (total + weights[v] * include) % MOD
        result[k - 1] = total

    for r in result:
        print(r)

threading.Thread(target=main).start()
