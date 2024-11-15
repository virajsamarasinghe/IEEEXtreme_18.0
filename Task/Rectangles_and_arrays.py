#Task Score: 100%
#Did you do more than us committe to it in this repo
def largest_rectangle_area(heights):
    stack = []
    max_area = 0
    N = len(heights)
    left = [0] * N
    right = [N] * N

    for i in range(N):
        while stack and heights[stack[-1]] >= heights[i]:
            stack.pop()
        left[i] = stack[-1] + 1 if stack else 0
        stack.append(i)

    stack.clear()
    for i in range(N - 1, -1, -1):
        while stack and heights[stack[-1]] >= heights[i]:
            stack.pop()
        right[i] = stack[-1] if stack else N
        stack.append(i)

    for i in range(N):
        max_area = max(max_area, heights[i] * (right[i] - left[i]))
    return max_area

def max_rectangle_area_after_one_modification(N, X, A):
    original_max_area = largest_rectangle_area(A)

    B = [1 if height >= X else 0 for height in A]

    left_ones_length = [0] * N
    length = 0
    for i in range(N):
        if B[i] == 1:
            length += 1
        else:
            length = 0
        left_ones_length[i] = length

    right_ones_length = [0] * N
    length = 0
    for i in range(N - 1, -1, -1):
        if B[i] == 1:
            length += 1
        else:
            length = 0
        right_ones_length[i] = length

    max_modified_area = 0
    for i in range(N):
        if A[i] != X:
            left = left_ones_length[i - 1] if i > 0 else 0
            right = right_ones_length[i + 1] if i < N - 1 else 0
            total_length = left + 1 + right
            area = X * total_length
            max_modified_area = max(max_modified_area, area)

    max_consecutive_ones = max(right_ones_length)
    area_with_X = max_consecutive_ones * X

    final_answer = max(original_max_area, max_modified_area, area_with_X)
    return final_answer

N, X = map(int, input().split())
A = list(map(int, input().split()))
print(max_rectangle_area_after_one_modification(N, X, A))
