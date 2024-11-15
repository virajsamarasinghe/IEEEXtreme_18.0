def calculate_union_area(N, K, L):
    area_of_one_square = 4 * L * L
    
    total_area = N * area_of_one_square
    
    if K >= 2 * L:
        overlap_area = 0
    else:
        overlap_area = (2 * L - K) * (2 * L - K) * (N - 1)
    
    union_area = total_area - overlap_area
    
    return union_area

# Input
N, K, L = map(int, input().split())

print(calculate_union_area(N, K, L))


#100% marks