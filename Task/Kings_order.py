import heapq
from collections import defaultdict

def f(n, m, g, d):
    a = defaultdict(list)
    i = [0] * n

    for x, y in d:
        a[x].append(y)
        i[y] += 1

    p = []
    for x in range(n):
        if i[x] == 0:
            heapq.heappush(p, (g[x], x))

    r = []
    while p:
        x, y = heapq.heappop(p)
        r.append(y + 1)
        for z in a[y]:
            i[z] -= 1
            if i[z] == 0:
                heapq.heappush(p, (g[z], z))

    if len(r) != n:
        return [-1]
    
    return r

n, m = map(int, input().split())
g = list(map(int, input().split()))
d = [tuple(map(lambda x: int(x) - 1, input().split())) for _ in range(m)]

o = f(n, m, g, d)
print(" ".join(map(str, o)))
