#include <iostream>
#include <unordered_map>
#include <cmath>
#include <cstdio>

struct S {
    int R1, B1, R2, B2, t;
    S(int R1, int B1, int R2, int B2, int t)
        : R1(R1), B1(B1), R2(R2), B2(B2), t(t) {}
    bool operator==(const S& o) const {
        return R1 == o.R1 && B1 == o.B1 && R2 == o.R2 && B2 == o.B2 && t == o.t;
    }
};

namespace std {
    template <>
    struct hash<S> {
        size_t operator()(const S& s) const {
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

std::unordered_map<S, double> m;

double v(int R1, int B1, int R2, int B2, int t) {
    if (R1 == 0 || B1 == 0) return 0.0;
    if (R2 == 0 || B2 == 0) return 1.0;
    S key(R1, B1, R2, B2, t);
    auto it = m.find(key);
    if (it != m.end()) {
        return it->second;
    }
    double best;
    if (t == 0) {
        double V11 = R1 > 0 ? v(R1 - 1, B1, R2, B2, 1) : 0.0;
        double V12 = B2 > 0 ? v(R1, B1, R2, B2 - 1, 1) : 1.0;
        double V21 = R2 > 0 ? v(R1, B1, R2 - 1, B2, 1) : 1.0;
        double V22 = B1 > 0 ? v(R1, B1 - 1, R2, B2, 1) : 0.0;

        double V1 = std::min(V11, V12);
        double V0 = std::min(V21, V22);
        best = std::max(V1, V0);

        double d = V11 - V12 - V21 + V22;
        double n = V22 - V21;
        if (fabs(d) > 1e-8) {
            double p = n / d;
            p = std::max(0.0, std::min(1.0, p));
            double E_red = p * V11 + (1 - p) * V21;
            double E_blue = p * V12 + (1 - p) * V22;
            double V_mix = std::min(E_red, E_blue);
            best = std::max(best, V_mix);
        } else {
            if (fabs(n) < 1e-8) {
                double p = 0.5;
                double E_red = p * V11 + (1 - p) * V21;
                double E_blue = p * V12 + (1 - p) * V22;
                double V_mix = std::min(E_red, E_blue);
                best = std::max(best, V_mix);
            } else {
                best = std::max(best, std::max(V1, V0));
            }
        }
    } else {
        double V11 = B1 > 0 ? v(R1, B1 - 1, R2, B2, 0) : 0.0;
        double V12 = R2 > 0 ? v(R1, B1, R2 - 1, B2, 0) : 1.0;
        double V21 = B2 > 0 ? v(R1, B1, R2, B2 - 1, 0) : 1.0;
        double V22 = R1 > 0 ? v(R1 - 1, B1, R2, B2, 0) : 0.0;

        double V1 = std::max(V11, V12);
        double V0 = std::max(V21, V22);
        best = std::min(V1, V0);

        double d = V11 - V12 - V21 + V22;
        double n = V22 - V21;
        if (fabs(d) > 1e-8) {
            double p = n / d;
            p = std::max(0.0, std::min(1.0, p));
            double E_red = p * V11 + (1 - p) * V21;
            double E_blue = p * V12 + (1 - p) * V22;
            double V_mix = std::max(E_red, E_blue);
            best = std::min(best, V_mix);
        } else {
            if (fabs(n) < 1e-8) {
                double p = 0.5;
                double E_red = p * V11 + (1 - p) * V21;
                double E_blue = p * V12 + (1 - p) * V22;
                double V_mix = std::max(E_red, E_blue);
                best = std::min(best, V_mix);
            } else {
                best = std::min(best, std::min(V1, V0));
            }
        }
    }
    m[key] = best;
    return best;
}

int main() {
    int R1, B1, R2, B2;
    std::cin >> R1 >> B1 >> R2 >> B2;
    double result = v(R1, B1, R2, B2, 0);
    printf("%.10f\n", result);
    return 0;
}
