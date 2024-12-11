def u(N, K, L):
    a = 4 * L * L
    t = N * a
    o = (2 * L - K) * (2 * L - K) * (N - 1) if K < 2 * L else 0
    return t - o

# Input
N, K, L = map(int, input().split())

print(u(N, K, L))
