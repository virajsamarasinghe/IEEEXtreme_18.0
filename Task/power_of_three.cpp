#include <iostream> 
#include <string> 
#include <cmath> 
#include <vector> 
#include <iomanip> 
using namespace std; 

typedef long long EnormousInt;
typedef long double GiantFloat;

EnormousInt compute_power_modulo(EnormousInt base, EnormousInt exponent, EnormousInt modulo) { 
    EnormousInt result = 1; 
    base %= modulo; 
    while (exponent > 0) { 
        if (exponent & 1) 
            result = result * base % modulo; 
        base = base * base % modulo; 
        exponent >>= 1; 
    } 
    return result; 
} 

EnormousInt compute_modulo_from_string(const string& number_string, EnormousInt modulo) { 
    EnormousInt result = 0; 
    for (char digit : number_string) { 
        result = (result * 10 + (digit - '0')) % modulo; 
    } 
    return result; 
} 

int main() { 
    string number_string; 
    cin >> number_string; 
    int number_length = number_string.size(); 
    int head_length = min(number_length, 15);
    string head_string = number_string.substr(0, head_length); 
    GiantFloat head_value = stold(head_string);

    GiantFloat log_number = log(head_value) + (number_length - head_length) * log(10.0L); 
    GiantFloat power_approx = log_number / log(3.0L); 
    EnormousInt power_integer = llround(power_approx); 

    if (fabsl(power_approx - power_integer) > 1e-6L) { 
        cout << -1 << endl; 
        return 0; 
    } 

    vector<EnormousInt> modulo_set = {1000000007LL, 1000000009LL, 1000000021LL}; 
    vector<EnormousInt> number_mod_results; 
    for (EnormousInt modulo : modulo_set) { 
        number_mod_results.push_back(compute_modulo_from_string(number_string, modulo)); 
    } 

    vector<EnormousInt> power_mod_results; 
    for (EnormousInt modulo : modulo_set) { 
        power_mod_results.push_back(compute_power_modulo(3LL, power_integer, modulo)); 
    } 

    bool match_found = true; 
    for (size_t index = 0; index < modulo_set.size(); ++index) { 
        if (number_mod_results[index] != power_mod_results[index]) { 
            match_found = false; 
            break; 
        } 
    } 

    if (match_found) { 
        cout << power_integer << endl; 
    } else { 
        cout << -1 << endl; 
    } 

    return 0; 
}


//100% marks