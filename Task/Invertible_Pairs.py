#Task Score: 55%
#Did you do more than us committe to it in this repo

def calculate_max_sum(n, values):
    max_subarray = [0] * n
    max_subarray[0] = values[0]
    max_result = max_subarray[0]
    
    for i in range(1, n):
        current_val = values[i]
        
        if i % 2 == 1:
            prev_val = values[i-1]
            without_flip = max(current_val, max_subarray[i-1] + current_val)
            flipped_prev = -prev_val
            flipped_curr = -current_val
            
            if i >= 2:
                with_flip = max(flipped_curr, max(max_subarray[i-2] + flipped_prev + flipped_curr, flipped_prev + flipped_curr))
            else:
                with_flip = max(flipped_curr, flipped_prev + flipped_curr)
            
            max_subarray[i] = max(without_flip, with_flip)
        else:
            max_subarray[i] = max(current_val, max_subarray[i-1] + current_val)
        
        max_result = max(max_result, max_subarray[i])
    
    return max_result

def main():
    test_cases = int(input())
    for _ in range(test_cases):
        num_elements = int(input())
        values = list(map(int, input().split()))
        result = calculate_max_sum(num_elements, values)
        print(result)

if __name__ == "__main__":
    main()
