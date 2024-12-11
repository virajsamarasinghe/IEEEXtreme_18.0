#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>
using namespace std;

union F {
    float f;
    uint32_t i;
    F() : i(0) {}
};

uint32_t nandOp(uint32_t a, uint32_t b) {
    return ~(a & b);
}

float fmaOp(float a, float b, float c) {
    return fmaf(a, b, c);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        string h;
        cin >> h;
        
        F C;
        C.i = stoul(h, nullptr, 16);
        
        int L;
        cin >> L;
        vector<vector<F>> luts(L);
        
        for (int i = 0; i < L; i++) {
            int s;
            cin >> s;
            luts[i].resize(s);
            for (int j = 0; j < s; j++) {
                string hex;
                cin >> hex;
                luts[i][j].i = stoul(hex, nullptr, 16);
            }
        }
        
        int Q;
        cin >> Q;
        vector<F> vals = {C};
        
        for (int i = 0; i < Q; i++) {
            string cmd;
            cin >> cmd;
            
            F res;
            
            if (cmd == "L") {
                int li, j, b;
                cin >> li >> j >> b;
                uint32_t mask = (vals[0].i >> j) & ((1u << b) - 1);
                res = luts[li][mask];
                
            } else if (cmd == "N") {
                int i1, i2;
                cin >> i1 >> i2;
                res.i = nandOp(vals[i1].i, vals[i2].i);
                
            } else if (cmd == "F") {
                int i1, i2, i3;
                cin >> i1 >> i2 >> i3;
                res.f = fmaOp(vals[i1].f, vals[i2].f, vals[i3].f);
                
            } else if (cmd == "C") {
                string hex;
                cin >> hex;
                res.i = stoul(hex, nullptr, 16);
            }
            
            vals.push_back(res);
        }
        
        cout << hex << setfill('0') << setw(8) << vals.back().i << endl;
    }
    
    return 0;
}
