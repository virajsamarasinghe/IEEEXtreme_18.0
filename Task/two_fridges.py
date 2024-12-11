def solve_fridge_temps(N, intervals):
    if N == 0:
        return -100, -100

    best_T1, best_T2 = float('inf'), float('inf')
    
    for T1 in range(-100, 101):
        for T2 in range(T1, 101):
            if all((a <= T1 <= b) or (a <= T2 <= b) for a, b in intervals):
                if T1 < best_T1 or (T1 == best_T1 and T2 < best_T2):
                    best_T1, best_T2 = T1, T2
    
    return (best_T1, best_T2) if best_T1 != float('inf') else (-1, -1)

def main():
    N = int(input())
    intervals = [tuple(map(int, input().split())) for _ in range(N)]
    
    T1, T2 = solve_fridge_temps(N, intervals)
    print(f"{T1} {T2}" if T1 != -1 else -1)

if __name__ == "__main__":
    main()
