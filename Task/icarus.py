def sprout(s):
    m = 2 * len(s)
    l, r = [0] * (m + 1), [0] * (m + 1)
    for p in range(1, m + 1):
        l[p] = 2 * p if 2 * p <= m else 0
        r[p] = 2 * p + 1 if 2 * p + 1 <= m else 0
    return l, r, m

def dance(s, start, l, r):
    p = start
    f = {p}
    for t in s:
        if t == 'L': p = l[p]
        elif t == 'R': p = r[p]
        elif t == 'U': p = p // 2
        if p != 0: f.add(p)
    return f

def main():
    import sys
    s = sys.stdin.read().strip()
    l, r, m = sprout(s)
    start = 2
    f = dance(s, start, l, r)
    for i in range(1, m + 1):
        if i not in f:
            break
    else:
        print(-1)
        return
    print(m, start, i)
    for i in range(1, m + 1):
        print(l[i], r[i])

if __name__ == "__main__":
    main()
