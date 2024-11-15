//Task Score: 20%
//Did you do more than us committe to it in this repo
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

bool isValidSequenceLength(int length) {
    return length % 4 == 0 || length % 4 == 1;
}

string constructDoubledSequence(int length) {
    if (!isValidSequenceLength(length)) {
        return "-1";
    }

    if (length == 1) {
        return "1 1";
    }

    if (length == 4) {
        return "1 1 3 4 2 3 2 4";
    }

    if (length == 5) {
        return "5 2 4 2 3 5 4 3 1 1";
    }

    if (length == 8) {
        return "8 6 4 7 1 1 4 6 8 5 7 2 3 2 5 3";
    }

    if (length == 9) {
        return "9 7 8 4 2 6 2 4 7 9 8 6 5 3 1 1 3 5";
    }

    if (length == 12) {
        return "12 10 11 7 5 9 2 8 2 5 7 10 12 11 9 8 6 4 1 1 3 4 6 3";
    }

    if (length == 13) {
        return "13 11 12 8 6 10 1 1 9 7 6 8 11 13 12 10 7 9 5 2 4 2 3 5 4 3";
    }

    vector<int> sequence(2 * length, 0);
    vector<bool> isUsed(length + 1, false);

    auto isValidPlacement = [&](int value, int index1, int index2) {
        if (index1 < 0 || index2 >= 2 * length || sequence[index1] != 0 || sequence[index2] != 0) {
            return false;
        }
        return index2 - index1 == value;
    };

    function<bool(int)> backtrackSequence = [&](int position) {
        if (position >= 2 * length) {
            return true;
        }
        if (sequence[position] != 0) {
            return backtrackSequence(position + 1);
        }

        for (int number = length; number >= 1; --number) {
            if (!isUsed[number] && isValidPlacement(number, position, position + number)) {
                sequence[position] = number;
                sequence[position + number] = number;
                isUsed[number] = true;

                if (backtrackSequence(position + 1)) {
                    return true;
                }

                sequence[position] = 0;
                sequence[position + number] = 0;
                isUsed[number] = false;
            }
        }
        return false;
    };

    if (backtrackSequence(0)) {
        string sequenceStr;
        for (int value : sequence) {
            sequenceStr += to_string(value) + " ";
        }
        sequenceStr.pop_back();  // Remove trailing space
        return sequenceStr;
    }
    return "-1";
}

int main() {
    int testCases;
    cin >> testCases;
    vector<string> outputs;

    for (int i = 0; i < testCases; ++i) {
        int sequenceLength;
        cin >> sequenceLength;
        outputs.push_back(constructDoubledSequence(sequenceLength));
    }

    for (const string& output : outputs) {
        cout << output << endl;
    }

    return 0;
}
