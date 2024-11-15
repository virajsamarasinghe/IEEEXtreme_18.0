#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

ll find_maximum_after_swaps(ll number, int swaps_remaining) {
    string digit_string = to_string(number);
    int num_digits = digit_string.length();
    
    if (swaps_remaining == 0) return number;
    
    for (int i = 0; i < num_digits; i++) {
        char current_digit = digit_string[i];
        char max_digit_in_suffix = *max_element(digit_string.begin() + i, digit_string.end());
        
        if (max_digit_in_suffix > current_digit) {
            vector<int> max_digit_positions;
            for (int j = num_digits - 1; j >= i; j--) {
                if (digit_string[j] == max_digit_in_suffix) {
                    max_digit_positions.push_back(j);
                }
            }
            
            ll maximum_result = number;
            for (int position : max_digit_positions) {
                string new_digit_string = digit_string;
                swap(new_digit_string[i], new_digit_string[position]);
                
                int remaining_swaps = swaps_remaining - 1;
                if (remaining_swaps > 0) {
                    ll result_after_swap = find_maximum_after_swaps(stoll(new_digit_string), remaining_swaps);
                    maximum_result = max(maximum_result, result_after_swap);
                } else {
                    maximum_result = max(maximum_result, stoll(new_digit_string));
                }
            }
            return maximum_result;
        }
    }
    
    return number;
}

int main() {
    ll number;
    int swaps;
    cin >> number >> swaps;
    
    ll result = find_maximum_after_swaps(number, swaps);
    cout << result << endl;

    return 0;
}