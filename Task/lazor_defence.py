import bisect

l, n1, n2 = map(int, input().split())

f, s = [], []

t = n1 + 1

for _ in range(n1):
    d, p = input().split()
    p = int(p)
    if d == 'U':
        f.append(p)
    elif d == 'R':
        f.append(l)
    elif d == 'L':
        f.append(0)

for _ in range(n2):
    d, p = input().split()
    p = int(p)
    if d == 'U':
        s.append(p)
    elif d == 'R':
        s.append(l)
    elif d == 'L':
        s.append(0)

f.sort()

for p in s:
    t += len(f) - bisect.bisect_right(f, p) + 1

print(t)
