#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

bool isValidLen(int len) {
    return len % 4 == 0 || len % 4 == 1;
}

string buildSeq(int len) {
    if (!isValidLen(len)) {
        return "-1";
    }

    if (len == 1) {
        return "1 1";
    }

    if (len == 4) {
        return "1 1 3 4 2 3 2 4";
    }

    if (len == 5) {
        return "5 2 4 2 3 5 4 3 1 1";
    }

    if (len == 8) {
        return "8 6 4 7 1 1 4 6 8 5 7 2 3 2 5 3";
    }

    if (len == 9) {
        return "9 7 8 4 2 6 2 4 7 9 8 6 5 3 1 1 3 5";
    }

    if (len == 12) {
        return "12 10 11 7 5 9 2 8 2 5 7 10 12 11 9 8 6 4 1 1 3 4 6 3";
    }

    if (len == 13) {
        return "13 11 12 8 6 10 1 1 9 7 6 8 11 13 12 10 7 9 5 2 4 2 3 5 4 3";
    }

    vector<int> seq(2 * len, 0);
    vector<bool> used(len + 1, false);

    auto validPlace = [&](int val, int i1, int i2) {
        if (i1 < 0 || i2 >= 2 * len || seq[i1] != 0 || seq[i2] != 0) {
            return false;
        }
        return i2 - i1 == val;
    };

    function<bool(int)> backtrack = [&](int pos) {
        if (pos >= 2 * len) {
            return true;
        }
        if (seq[pos] != 0) {
            return backtrack(pos + 1);
        }

        for (int num = len; num >= 1; --num) {
            if (!used[num] && validPlace(num, pos, pos + num)) {
                seq[pos] = num;
                seq[pos + num] = num;
                used[num] = true;

                if (backtrack(pos + 1)) {
                    return true;
                }

                seq[pos] = 0;
                seq[pos + num] = 0;
                used[num] = false;
            }
        }
        return false;
    };

    if (backtrack(0)) {
        string res;
        for (int v : seq) {
            res += to_string(v) + " ";
        }
        res.pop_back();  
        return res;
    }
    return "-1";
}

int main() {
    int t;
    cin >> t;
    vector<string> out;

    for (int i = 0; i < t; ++i) {
        int len;
        cin >> len;
        out.push_back(buildSeq(len));
    }

    for (const string& str : out) {
        cout << str << endl;
    }

    return 0;
}
