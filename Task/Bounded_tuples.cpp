//Task Score: 50%
//Did you do more than us committe to it in this repo

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std; 
const int MODULO = 998244353; 
 
inline int addModulo(int x, int y) { 
    x += y; 
    if (x >= MODULO) x -= MODULO; 
    return x; 
} 
 
int main() { 
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr); 
     
    int numVariables, numConstraints; 
    cin >> numVariables >> numConstraints; 
     
    if (numConstraints == 0 && numVariables > 0) { 
        cout << "infinity\n"; 
        return 0; 
    } 
     
    vector<int> lowerBounds(numConstraints), upperBounds(numConstraints); 
    vector<vector<int>> constraintVariables(numConstraints); 
     
    int maximumValue = 0; 
    for (int i = 0; i < numConstraints; i++) { 
        int count; 
        cin >> lowerBounds[i] >> upperBounds[i] >> count; 
        maximumValue = max(maximumValue, upperBounds[i]); 
         
        if (lowerBounds[i] > upperBounds[i]) { 
            cout << "0\n"; 
            return 0; 
        } 
         
        constraintVariables[i].resize(count); 
        for (int j = 0; j < count; j++) { 
            cin >> constraintVariables[i][j]; 
            constraintVariables[i][j]--; // Convert to 0-based indexing 
        } 
    } 
     
    vector<bool> hasConstraint(numVariables, false); 
    vector<vector<int>> variableToConstraints(numVariables); 
    for (int i = 0; i < numConstraints; i++) { 
        for (int variable : constraintVariables[i]) { 
            hasConstraint[variable] = true; 
            variableToConstraints[variable].push_back(i); 
        } 
    } 
     
    for (int i = 0; i < numVariables; i++) { 
        if (!hasConstraint[i]) { 
            cout << "infinity\n"; 
            return 0; 
        } 
    } 
     
    int solutionCount = 0; 
    vector<int> variableValues(numVariables); 
     
    function<void(int)> searchSolutions = [&](int position) { 
        if (position == numVariables) { 
            solutionCount = addModulo(solutionCount, 1); 
            return; 
        } 
         
        const auto& currentConstraints = variableToConstraints[position]; 
         
        for (int value = 0; value <= maximumValue; value++) { 
            variableValues[position] = value; 
            bool isValid = true; 
             
            for (int constraintIndex : currentConstraints) { 
                int sum = 0; 
                bool allVariablesAssigned = true; 
                 
                for (int variable : constraintVariables[constraintIndex]) { 
                    if (variable > position) { 
                        allVariablesAssigned = false; 
                        break; 
                    } 
                    sum += variableValues[variable]; 
                } 
                 
                if (allVariablesAssigned) { 
                    if (sum < lowerBounds[constraintIndex] || sum > upperBounds[constraintIndex]) { 
                        isValid = false; 
                        break; 
                    } 
                } else if (sum > upperBounds[constraintIndex]) { 
                    isValid = false; 
                    break; 
                } 
            } 
             
            if (isValid) searchSolutions(position + 1); 
        } 
    }; 
     
    searchSolutions(0); 
    cout << solutionCount << "\n"; 
    return 0; 
}
