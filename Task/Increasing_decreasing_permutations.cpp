//Task Score: 30%
//Did you do more than us committe to it in this repo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

struct VectorHasher {
    size_t operator()(const vector<int>& vec) const {
        size_t vecHash = 0;
        for (int value : vec) {
            vecHash ^= vecHash * 31 + value;
        }
        return vecHash;
    }
};

unordered_set<vector<int>, VectorHasher> generateValidSequences(int size) {
    int midPoint = (size + 1) / 2;
    unordered_set<vector<int>, VectorHasher> validSequences;
    vector<int> sequence(size);
    iota(sequence.begin(), sequence.end(), 1);

    do {
        bool isValid = true;
        for (int i = 0; i < midPoint - 1; i++) {
            if (sequence[i] >= sequence[i + 1]) {
                isValid = false;
                break;
            }
        }
        for (int i = midPoint - 1; i < size - 1 && isValid; i++) {
            if (sequence[i] <= sequence[i + 1]) {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            validSequences.insert(sequence);
        }
    } while (next_permutation(sequence.begin(), sequence.end()));

    return validSequences;
}

unordered_map<vector<int>, int, VectorHasher> calculateMinSwaps(
    const unordered_set<vector<int>, VectorHasher>& validSequences, int size) {
    
    unordered_map<vector<int>, int, VectorHasher> swapCounts;
    queue<pair<vector<int>, int>> bfsQueue;

    for (const auto& validSequence : validSequences) {
        bfsQueue.push({validSequence, 0});
        swapCounts[validSequence] = 0;
    }

    while (!bfsQueue.empty()) {
        auto [currentSequence, swapCount] = bfsQueue.front();
        bfsQueue.pop();

        for (int i = 0; i < size - 1; i++) {
            vector<int> newSequence = currentSequence;
            swap(newSequence[i], newSequence[i + 1]);

            if (swapCounts.find(newSequence) == swapCounts.end()) {
                swapCounts[newSequence] = swapCount + 1;
                bfsQueue.push({newSequence, swapCount + 1});
            }
        }
    }

    return swapCounts;
}

int solveProblem(int size, int modulo) {
    auto validSequences = generateValidSequences(size);
    auto swapCounts = calculateMinSwaps(validSequences, size);

    vector<int> initialSequence(size);
    iota(initialSequence.begin(), initialSequence.end(), 1);

    int totalSwaps = 0;
    do {
        totalSwaps = (totalSwaps + swapCounts[initialSequence]) % modulo;
    } while (next_permutation(initialSequence.begin(), initialSequence.end()));

    return totalSwaps;
}

int main() {
    int size, modulo;
    cin >> size >> modulo;
    cout << solveProblem(size, modulo) << endl;
    return 0;
}
