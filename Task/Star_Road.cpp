#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class R {
private:
    vector<vector<int>> a;
    vector<int> r;
    int m;
    int n;
    
    void d(int c, int p, vector<int>& cp) {
        if (cp.capacity() < r.size()) {
            cp.reserve(r.size());
        }
        
        auto pos = lower_bound(cp.begin(), cp.end(), r[c]);
        bool ins = false;
        
        if (pos == cp.end()) {
            cp.push_back(r[c]);
            ins = true;
        } else {
            int v = *pos;
            *pos = r[c];
            m = max(m, (int)cp.size());
            
            for (const int& nbr : a[c]) {
                if (nbr != p) {
                    d(nbr, c, cp);
                }
            }
            
            *pos = v;
            return;
        }
        
        m = max(m, (int)cp.size());
        
        for (const int& nbr : a[c]) {
            if (nbr != p) {
                d(nbr, c, cp);
            }
        }
        
        if (ins) {
            cp.pop_back();
        }
    }

public:
    R(int s) : n(s), m(0) {
        a.resize(s);
        r.resize(s);
    }
    
    void s(int i, int v) {
        r[i] = v;
    }
    
    void aC(int c1, int c2) {
        a[c1].push_back(c2);
        a[c2].push_back(c1);
    }
    
    int f() {
        vector<int> cp;
        cp.reserve(n); 
        
        for (int i = 0; i < n; i++) {
            if (a[i].size() == 1) { 
                d(i, -1, cp);
            }
        }
        
        return m;
    }
};

int main() {
    ios_base::sync_with_stdio(false);  
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    R f(n);
    
    for (int i = 0; i < n; i++) {
        int sr;
        cin >> sr;
        f.s(i, sr);
    }
    
    for (int i = 0; i < n - 1; i++) {
        int c1, c2;
        cin >> c1 >> c2;
        f.aC(--c1, --c2);
    }
    
    cout << f.f() << endl;
    
    return 0;
}
