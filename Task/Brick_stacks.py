def solve(N, x, A):
    A.sort()
    
    def is_valid(k):
        for i in range(k, N):
            if A[i - k] + x > A[i]:
                return False
        return True

    lo, hi = 1, N
    while lo < hi:
        mid = (lo + hi) // 2
        if is_valid(mid):
            hi = mid
        else:
            lo = mid + 1

    k = lo

    stacks = [[] for _ in range(k)]
    for i in range(N):
        stacks[i % k].append(A[i])

    print(k)
    for stack in stacks:
        stack.reverse()
        print(len(stack), *stack)
    
N, x = map(int, input().split())
A = list(map(int, input().split()))
solve(N, x, A)
