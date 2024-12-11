def count_hit_tiles(tt, ne, el):
    if 1 in el:
        return tt

    el = [e for e in el if e <= tt]
    ne = len(el)

    if ne == 0:
        return 0

    el.sort()
    hc = 0

    def recurse(idx, cp, sgn):
        nonlocal hc
        for i in range(idx, ne):
            e = el[i]
            np = cp * e
            if np > tt:
                break
            hc += sgn * (tt // np)
            recurse(i + 1, np, -sgn)

    recurse(0, 1, 1)
    return hc

if __name__ == "__main__":
    import sys

    data = sys.stdin.read().split()
    tt = int(data[0])
    ne = int(data[1])
    el = list(map(int, data[2:2 + ne]))

    print(count_hit_tiles(tt, ne, el))
