def solve(N, x, A):
    A_sorted = sorted(A)
    
    def is_valid(k):
        for i in range(k, N):
            if A_sorted[i - k] + x > A_sorted[i]:
                return False
        return True

    low = 1
    high = N
    while low < high:
        mid = (low + high) // 2
        if is_valid(mid):
            high = mid
        else:
            low = mid + 1

    k = low

    stacks = [[] for _ in range(k)]
    for i in range(N):
        stacks[i % k].append(A_sorted[i])

    print(k)
    for stack in stacks:
        stack.reverse()
        print(len(stack), *stack)
    
N, x = map(int, input().split())
A = list(map(int, input().split()))
solve(N, x, A)
