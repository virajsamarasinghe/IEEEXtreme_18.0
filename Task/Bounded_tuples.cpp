#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std; 
const int MOD = 998244353; 
 
inline int addMod(int x, int y) { 
    x += y; 
    if (x >= MOD) x -= MOD; 
    return x; 
} 
 
int main() { 
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr); 
     
    int n, m; 
    cin >> n >> m; 
     
    if (m == 0 && n > 0) { 
        cout << "infinity\n"; 
        return 0; 
    } 
     
    vector<int> lb(m), ub(m); 
    vector<vector<int>> conVars(m); 
     
    int maxVal = 0; 
    for (int i = 0; i < m; i++) { 
        int cnt; 
        cin >> lb[i] >> ub[i] >> cnt; 
        maxVal = max(maxVal, ub[i]); 
         
        if (lb[i] > ub[i]) { 
            cout << "0\n"; 
            return 0; 
        } 
         
        conVars[i].resize(cnt); 
        for (int j = 0; j < cnt; j++) { 
            cin >> conVars[i][j]; 
            conVars[i][j]--; 
        } 
    } 
     
    vector<bool> hasCon(n, false); 
    vector<vector<int>> varCon(n); 
    for (int i = 0; i < m; i++) { 
        for (int v : conVars[i]) { 
            hasCon[v] = true; 
            varCon[v].push_back(i); 
        } 
    } 
     
    for (int i = 0; i < n; i++) { 
        if (!hasCon[i]) { 
            cout << "infinity\n"; 
            return 0; 
        } 
    } 
     
    int solCnt = 0; 
    vector<int> varVals(n); 
     
    function<void(int)> dfs = [&](int pos) { 
        if (pos == n) { 
            solCnt = addMod(solCnt, 1); 
            return; 
        } 
         
        const auto& con = varCon[pos]; 
         
        for (int v = 0; v <= maxVal; v++) { 
            varVals[pos] = v; 
            bool valid = true; 
             
            for (int cIdx : con) { 
                int sum = 0; 
                bool allAssigned = true; 
                 
                for (int var : conVars[cIdx]) { 
                    if (var > pos) { 
                        allAssigned = false; 
                        break; 
                    } 
                    sum += varVals[var]; 
                } 
                 
                if (allAssigned) { 
                    if (sum < lb[cIdx] || sum > ub[cIdx]) { 
                        valid = false; 
                        break; 
                    } 
                } else if (sum > ub[cIdx]) { 
                    valid = false; 
                    break; 
                } 
            } 
             
            if (valid) dfs(pos + 1); 
        } 
    }; 
     
    dfs(0); 
    cout << solCnt << "\n"; 
    return 0; 
}
