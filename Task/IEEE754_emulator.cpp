#include <bits/stdc++.h>
using namespace std;

union FloatBits {
    float f;
    uint32_t i;

    FloatBits() : i(0) {}
};

uint32_t nandOperation(uint32_t a, uint32_t b) {
    return ~(a & b);
}

float fmaOperation(float a, float b, float c) {
    return fmaf(a, b, c);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        string initialHex;
        cin >> initialHex;
        
        FloatBits C0;
        C0.i = stoul(initialHex, nullptr, 16);
        
        int L;
        cin >> L;
        vector<vector<FloatBits>> luts(L);
        
        for (int i = 0; i < L; i++) {
            int size;
            cin >> size;
            luts[i].resize(size);
            for (int j = 0; j < size; j++) {
                string hex;
                cin >> hex;
                luts[i][j].i = stoul(hex, nullptr, 16);
            }
        }
        
        int Q;
        cin >> Q;
        vector<FloatBits> values;
        values.push_back(C0);
        
        for (int i = 0; i < Q; i++) {
            string cmd;
            cin >> cmd;
            
            FloatBits result;
            
            if (cmd == "L") {
                int lutIndex, j, b;
                cin >> lutIndex >> j >> b;
                
                uint32_t mask = (values[0].i >> j) & ((1u << b) - 1);
                result = luts[lutIndex][mask];
                
            } else if (cmd == "N") {
                int i1, i2;
                cin >> i1 >> i2;
                result.i = nandOperation(values[i1].i, values[i2].i);
                
            } else if (cmd == "F") {
                int i1, i2, i3;
                cin >> i1 >> i2 >> i3;
                result.f = fmaOperation(values[i1].f, values[i2].f, values[i3].f);
                
            } else if (cmd == "C") {
                string hex;
                cin >> hex;
                result.i = stoul(hex, nullptr, 16);
            }
            
            values.push_back(result);
        }
        
        cout << hex << setfill('0') << setw(8) << values.back().i << endl;
    }
    
    return 0;
}
//100% marks