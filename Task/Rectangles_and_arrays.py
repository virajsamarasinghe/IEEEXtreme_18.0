def lra(h):
    s = []
    m = 0
    N = len(h)
    l = [0] * N
    r = [N] * N

    for i in range(N):
        while s and h[s[-1]] >= h[i]:
            s.pop()
        l[i] = s[-1] + 1 if s else 0
        s.append(i)

    s.clear()
    for i in range(N - 1, -1, -1):
        while s and h[s[-1]] >= h[i]:
            s.pop()
        r[i] = s[-1] if s else N
        s.append(i)

    for i in range(N):
        m = max(m, h[i] * (r[i] - l[i]))
    return m

def mra(N, X, A):
    o = lra(A)

    B = [1 if a >= X else 0 for a in A]

    l1 = [0] * N
    m = 0
    for i in range(N):
        if B[i] == 1:
            m += 1
        else:
            m = 0
        l1[i] = m

    l2 = [0] * N
    m = 0
    for i in range(N - 1, -1, -1):
        if B[i] == 1:
            m += 1
        else:
            m = 0
        l2[i] = m

    ma = 0
    for i in range(N):
        if A[i] != X:
            l = l1[i - 1] if i > 0 else 0
            r = l2[i + 1] if i < N - 1 else 0
            l += 1
            area = X * (l + r)
            ma = max(ma, area)

    m1 = max(l2)
    area = m1 * X

    return max(o, ma, area)

N, X = map(int, input().split())
A = list(map(int, input().split()))
print(mra(N, X, A))
