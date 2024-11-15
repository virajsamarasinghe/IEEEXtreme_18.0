//Task Score: 25%
//Did you do more than us committe to it in this repo

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long calculateValidSum(const vector<int>& arr, int maxAllowedSum) {
    int length = arr.size();
    long long totalValidSum = 0;
    
    // Process subarrays
    for (int start = 0; start < length; start++) {
        int end = start;
        while (end < length) {
            int subArrayLength = end - start + 1;
            bool isValid = true;

            // Check pair sums for even-length subarrays
            if (subArrayLength % 2 == 0) {
                int maxPairSum = 0;
                for (int i = 0; i < subArrayLength / 2; i++) {
                    maxPairSum = max(maxPairSum, arr[start + i] + arr[end - i]);
                }
                isValid = maxPairSum <= maxAllowedSum;
            } 
            // Check pair and single element for odd-length subarrays
            else {
                int maxSingleElement = arr[end];
                int maxPairSum = 0;
                for (int i = 0; i < (subArrayLength - 1) / 2; i++) {
                    maxPairSum = max(maxPairSum, arr[start + i] + arr[end - 1 - i]);
                }
                isValid = max(maxSingleElement, maxPairSum) <= maxAllowedSum;
            }

            if (!isValid) break;

            totalValidSum += arr[end] - arr[start];
            end++;
        }
    }
    return totalValidSum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int arraySize, queries;
    cin >> arraySize >> queries;
    
    vector<int> arr(arraySize);
    for (int i = 0; i < arraySize; i++) {
        cin >> arr[i];
    }
    
    while (queries--) {
        int maxAllowedSum;
        cin >> maxAllowedSum;
        cout << calculateValidSum(arr, maxAllowedSum) << '\n';
    }
    
    return 0;
}
