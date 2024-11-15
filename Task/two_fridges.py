def solve_fridge_temps(N, intervals):
    if N == 0:
        return -100, -100


    best_T1 = float('inf')
    best_T2 = float('inf')
    found_solution = False

  
    for T1 in range(-100, 101):
     
        for T2 in range(T1, 101):
            valid = True
            
            for a, b in intervals:
                
                if not ((a <= T1 <= b) or (a <= T2 <= b)):
                    valid = False
                    break
            
            if valid:
                found_solution = True
                
                if T1 < best_T1 or (T1 == best_T1 and T2 < best_T2):
                    best_T1 = T1
                    best_T2 = T2
                break  
    
    if not found_solution:
        return -1, -1
    return best_T1, best_T2

def main():
    
    N = int(input())
    intervals = []
    for _ in range(N):
        a, b = map(int, input().split())
        intervals.append((a, b))
    
    
    T1, T2 = solve_fridge_temps(N, intervals)
    if T1 == -1:
        print(-1)
    else:
        print(f"{T1} {T2}")

if __name__ == "__main__":
    main()