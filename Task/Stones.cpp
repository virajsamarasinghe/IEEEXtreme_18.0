//Task Score: 100%
//Did you do more than us committe to it in this repo

#include <iostream>
#include <unordered_map>
#include <cmath>
#include <cstdio>

struct State {
    int R1, B1, R2, B2, t;
    State(int R1, int B1, int R2, int B2, int t)
        : R1(R1), B1(B1), R2(R2), B2(B2), t(t) {}
    bool operator==(const State& other) const {
        return R1 == other.R1 && B1 == other.B1 && R2 == other.R2 && B2 == other.B2 && t == other.t;
    }
};

namespace std {
    template <>
    struct hash<State> {
        size_t operator()(const State& s) const {
            size_t res = 17;
            res = res * 31 + hash<int>()(s.R1);
            res = res * 31 + hash<int>()(s.B1);
            res = res * 31 + hash<int>()(s.R2);
            res = res * 31 + hash<int>()(s.B2);
            res = res * 31 + hash<int>()(s.t);
            return res;
        }
    };
}

std::unordered_map<State, double> memo;

double V(int R1, int B1, int R2, int B2, int t) {
    if (R1 == 0 || B1 == 0) return 0.0;
    if (R2 == 0 || B2 == 0) return 1.0;
    State key(R1, B1, R2, B2, t);
    auto it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }
    double V_best;
    if (t == 0) {
        double V11 = R1 > 0 ? V(R1 - 1, B1, R2, B2, 1) : 0.0;
        double V12 = B2 > 0 ? V(R1, B1, R2, B2 - 1, 1) : 1.0;
        double V21 = R2 > 0 ? V(R1, B1, R2 - 1, B2, 1) : 1.0;
        double V22 = B1 > 0 ? V(R1, B1 - 1, R2, B2, 1) : 0.0;

        double V1 = std::min(V11, V12);
        double V0 = std::min(V21, V22);
        V_best = std::max(V1, V0);

        double denominator = V11 - V12 - V21 + V22;
        double numerator = V22 - V21;
        if (fabs(denominator) > 1e-8) {
            double p = numerator / denominator;
            p = std::max(0.0, std::min(1.0, p));
            double E_red = p * V11 + (1 - p) * V21;
            double E_blue = p * V12 + (1 - p) * V22;
            double V_mix = std::min(E_red, E_blue);
            V_best = std::max(V_best, V_mix);
        } else {
            if (fabs(numerator) < 1e-8) {
                double p = 0.5;
                double E_red = p * V11 + (1 - p) * V21;
                double E_blue = p * V12 + (1 - p) * V22;
                double V_mix = std::min(E_red, E_blue);
                V_best = std::max(V_best, V_mix);
            } else {
                V_best = std::max(V_best, std::max(V1, V0));
            }
        }
    } else {
        double V11 = B1 > 0 ? V(R1, B1 - 1, R2, B2, 0) : 0.0;
        double V12 = R2 > 0 ? V(R1, B1, R2 - 1, B2, 0) : 1.0;
        double V21 = B2 > 0 ? V(R1, B1, R2, B2 - 1, 0) : 1.0;
        double V22 = R1 > 0 ? V(R1 - 1, B1, R2, B2, 0) : 0.0;

        double V1 = std::max(V11, V12);
        double V0 = std::max(V21, V22);
        V_best = std::min(V1, V0);

        double denominator = V11 - V12 - V21 + V22;
        double numerator = V22 - V21;
        if (fabs(denominator) > 1e-8) {
            double p = numerator / denominator;
            p = std::max(0.0, std::min(1.0, p));
            double E_red = p * V11 + (1 - p) * V21;
            double E_blue = p * V12 + (1 - p) * V22;
            double V_mix = std::max(E_red, E_blue);
            V_best = std::min(V_best, V_mix);
        } else {
            if (fabs(numerator) < 1e-8) {
                double p = 0.5;
                double E_red = p * V11 + (1 - p) * V21;
                double E_blue = p * V12 + (1 - p) * V22;
                double V_mix = std::max(E_red, E_blue);
                V_best = std::min(V_best, V_mix);
            } else {
                V_best = std::min(V_best, std::min(V1, V0));
            }
        }
    }
    memo[key] = V_best;
    return V_best;
}

int main() {
    int R1, B1, R2, B2;
    std::cin >> R1 >> B1 >> R2 >> B2;
    double result = V(R1, B1, R2, B2, 0);
    printf("%.10f\n", result);
    return 0;
}
