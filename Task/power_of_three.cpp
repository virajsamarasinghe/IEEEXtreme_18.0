#include <iostream> 
#include <string> 
#include <cmath> 
#include <vector> 
#include <iomanip> 
using namespace std; 

typedef long long E;
typedef long double G;

E pmod(E b, E e, E m) { 
    E r = 1; 
    b %= m; 
    while (e > 0) { 
        if (e & 1) 
            r = r * b % m; 
        b = b * b % m; 
        e >>= 1; 
    } 
    return r; 
} 

E mod_from_str(const string& s, E m) { 
    E r = 0; 
    for (char d : s) { 
        r = (r * 10 + (d - '0')) % m; 
    } 
    return r; 
} 

int main() { 
    string s; 
    cin >> s; 
    int n = s.size(); 
    int h = min(n, 15);
    string hs = s.substr(0, h); 
    G hv = stold(hs);

    G ln = log(hv) + (n - h) * log(10.0L); 
    G p_approx = ln / log(3.0L); 
    E p_int = llround(p_approx); 

    if (fabsl(p_approx - p_int) > 1e-6L) { 
        cout << -1 << endl; 
        return 0; 
    } 

    vector<E> ms = {1000000007LL, 1000000009LL, 1000000021LL}; 
    vector<E> nr; 
    for (E m : ms) { 
        nr.push_back(mod_from_str(s, m)); 
    } 

    vector<E> pr; 
    for (E m : ms) { 
        pr.push_back(pmod(3LL, p_int, m)); 
    } 

    bool match = true; 
    for (size_t i = 0; i < ms.size(); ++i) { 
        if (nr[i] != pr[i]) { 
            match = false; 
            break; 
        } 
    } 

    if (match) { 
        cout << p_int << endl; 
    } else { 
        cout << -1 << endl; 
    } 

    return 0; 
}
