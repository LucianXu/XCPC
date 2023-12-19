// created on Lucian Xu's Laptop

#include <bits/stdc++.h>

// using namespace std;

#define typet typename T
#define typeu typename U
#define types typename... Ts
#define tempt template <typet>
#define tempu template <typeu>
#define temps template <types>
#define tandu template <typet, typeu>

using UI = unsigned int;
using ULL = unsigned long long;
using LL = long long;
using ULL = unsigned long long;
using i128 = __int128;
using PII = std::pair<int, int>;
using PIL = std::pair<int, LL>;
using PLI = std::pair<LL, int>;
using PLL = std::pair<LL, LL>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vl = std::vector<LL>;
using vvl = std::vector<vl>;
using vpi = std::vector<PII>;

#define ff first
#define ss second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) \
    do {           \
    } while (false)
#endif

constexpr int mod = 998244353;
constexpr int inv2 = (mod + 1) / 2;
constexpr int inf = 0x3f3f3f3f;
constexpr LL INF = 1e18;
constexpr double pi = 3.141592653589793;
constexpr double eps = 1e-6;

constexpr int lowbit(int x) { return x & -x; }
tandu bool Max(T& x, const U& y) { return x < y ? x = y, true : false; }
tandu bool Min(T& x, const U& y) { return x > y ? x = y, true : false; }

void solut() {
    int x, y, A, B;
    std::cin >> x >> y >> A >> B;
    if (x == y) {
        std::cout << "YES" << '\n';
        std::cout << 2 << ' ' << 2 << '\n';
        return;
    }
    std::map<vi, int> have;
    for (int a = 2; a <= A and 1ll * a * a <= x; a++) {
        int tmp = x;
        vi code;
        for (int tmp = x; tmp; tmp /= a) {
            code.push_back(tmp % a);
        }
        have[code] = a;
    }
    for (int b = 2; b <= B and 1ll * b * b <= y; b++) {
        int tmp = y;
        vi code;
        for (int tmp = y; tmp; tmp /= b) {
            code.push_back(tmp % b);
        }
        if (have.count(code)) {
            std::cout << "YES" << '\n';
            std::cout << have[code] << ' ' << b << '\n';
            return;
        }
    }
    int swaped = 0;
    if (x < y) {
        std::swap(x, y);
        std::swap(A, B);
        swaped = 1;
    }
    for (int t = 1; 1ll * t * t <= x; t++) {
        if ((x - y) % t == 0) {
            int L = 2, R = A;
            int z = (x - y) / t;
            Max(L, t + 1);
            Max(L, (x + t + 1) / (t + 1));
            Max(L, t + 1 + z);
            Max(L, (y + t + 1) / (t + 1) + z);
            Min(R, x / t);
            Min(R, y / t + z);
            Min(R, B + z);
            if (L <= R) {
                std::cout << "YES" << '\n';
                if (!swaped) {
                    std::cout << L << ' ' << (t * L - x + y) / t << '\n';
                } else {
                    std::cout << (t * L - x + y) / t << ' ' << L << '\n';
                }
                return;
            }
        }
    }
    std::cout << "NO" << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int t = 1;
    std::cin >> t;
    while (t--) {
        solut();
    }
    return 0;
}
