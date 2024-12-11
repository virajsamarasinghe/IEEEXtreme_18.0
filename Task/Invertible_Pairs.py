def f(n, v):
    m = [0] * n
    m[0] = v[0]
    r = m[0]
    
    for i in range(1, n):
        c = v[i]
        
        if i % 2 == 1:
            p = v[i-1]
            w = max(c, m[i-1] + c)
            fp = -p
            fc = -c
            
            if i >= 2:
                f2 = max(fc, max(m[i-2] + fp + fc, fp + fc))
            else:
                f2 = max(fc, fp + fc)
            
            m[i] = max(w, f2)
        else:
            m[i] = max(c, m[i-1] + c)
        
        r = max(r, m[i])
    
    return r

def main():
    t = int(input())
    for _ in range(t):
        n = int(input())
        v = list(map(int, input().split()))
        print(f(n, v))

if __name__ == "__main__":
    main()
