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
    int n, m;
    std::cin >> n >> m;
    if (n == 1) {
        std::cout << "NO" << '\n';
        return;
    }
    if (n == 2) {
        for (int i = 1; 2 * i <= m; i++) {
            if ((i ^ (m - i)) < i) {
                std::cout << "YES" << '\n';
                std::cout << i << ' ' << m - i << '\n';
                return;
            }
        }
        std::cout << "NO" << '\n';
        return;
    }
    if (~m & 1 and ~n & 1) {    // n 为偶数, m 为偶数 //
        std::cout << "YES" << '\n';
        for (int i = 1; i <= n - 2; i++) std::cout << 1 << ' ';
        std::cout << (m - n + 2) / 2 << ' ' << (m - n + 2) / 2 << '\n';
        return;
    }
    if (~m & 1 and n & 1) {    // n 为奇数, m 为偶数 //
        int k = m - n + 3;
        if (__builtin_popcount(k) != 1) {
            std::cout << "YES" << '\n';
            for (int i = 1; i <= n - 3; i++) std::cout << 1 << ' ';
            std::cout << k / 2 << ' ' << k / 2 - lowbit(k / 2) << ' ' << lowbit(k / 2) << '\n';
            return;
        }
        if (n == 3) {    // n = 3, k = 2 ^ p //
            if (k == 4 or k == 8) {
                std::cout << "NO" << '\n';
            } else {
                std::cout << "YES" << '\n';
                std::cout << 3 * k / 16 << ' ' << 6 * k / 16 << ' ' << 7 * k / 16 << '\n';
            }
            return;
        }
        if (n >= 5) {
            if (k == 4) {
                std::cout << "NO" << '\n';
            } else {
                std::cout << "YES" << '\n';
                k -= 2;
                for (int i = 1; i <= n - 5; i++) std::cout << 1 << ' ';
                std::cout << 2 << ' ' << 2 << '\n';
                std::cout << k / 2 << ' ' << k / 2 - lowbit(k / 2) << ' ' << lowbit(k / 2) << '\n';
            }
            return;
        }
    }
    if (m & 1 and ~n & 1) {    // n 为偶数, m 为奇数 //
        if (m < 2 * n) {
            std::cout << "NO" << '\n';
            return;
        }
        std::cout << "YES" << '\n';
        for (int i = 1; i <= n - 3; i++) std::cout << 2 << ' ';
        std::cout << 3 << ' ';
        std::cout << (m - 2 * n + 3) / 2 << ' ' << (m - 2 * n + 3) / 2 << '\n';
        return;
    }
    if (m & 1 and n & 1) {    // n 为奇数, m 为奇数 //
        if (m < 2 * n) {
            std::cout << "NO" << '\n';
            return;
        }
        int k = m - 2 * n + 6;
        if (__builtin_popcount(k - 1) != 1 and __builtin_popcount(k - 3) != 1) {
            std::cout << "YES" << '\n';
            int a = k / 2, b = k / 2 - lowbit(k / 2), c = lowbit(k / 2);
            if (c == 1) {
                int d = lowbit(b);
                b -= d, c += d;
                b++;
            } else {
                if (~b & 1) {
                    b += 1;
                } else {
                    c += 1;
                }
            }
            for (int i = 1; i <= n - 3; i++) std::cout << 2 << ' ';
            std::cout << a << ' ' << b << ' ' << c << '\n';
            return;
        }
        if (n == 3) {
            if (__builtin_popcount(k - 1) == 1) {
                if (k == 9 or k == 17) {
                    std::cout << "NO" << '\n';
                } else {
                    std::cout << "YES" << '\n';
                    std::cout << 3 * (k - 1) / 16 << ' ' << 6 * (k - 1) / 16 + 1 << ' '
                              << 7 * (k - 1) / 16 << '\n';
                }
                return;
            }
            if (__builtin_popcount(k - 3) == 1) {
                if (k == 7 or k == 11 or k == 19) {
                    std::cout << "NO" << '\n';
                } else {
                    std::cout << "YES" << '\n';
                    std::cout << 7 << ' ' << (m - 7) / 2 + 1 << ' ' << (m - 7) / 2 - 1 << '\n';
                }
                return;
            }
        }
        if (n >= 5) {
            if (__builtin_popcount(k - 1) == 1) {
                if (k <= 9) {
                    std::cout << "NO" << '\n';
                } else {
                    k -= 2;
                    std::cout << "YES" << '\n';
                    int a = k / 2, b = k / 2 - lowbit(k / 2), c = lowbit(k / 2);
                    if (c == 1) {
                        int d = lowbit(b);
                        b -= d, c += d;
                        b++;
                    } else {
                        if (~b & 1) {
                            b += 1;
                        } else {
                            c += 1;
                        }
                    }
                    for (int i = 1; i <= n - 5; i++) std::cout << 2 << ' ';
                    std::cout << 3 << ' ' << 3 << ' ';
                    std::cout << a << ' ' << b << ' ' << c << '\n';
                }
                return;
            }
            if (__builtin_popcount(k - 3) == 1) {
                if (k <= 11) {
                    std::cout << "NO" << '\n';
                } else {
                    k -= 4;
                    std::cout << "YES" << '\n';
                    int a = k / 2, b = k / 2 - lowbit(k / 2), c = lowbit(k / 2);
                    if (c == 1) {
                        int d = lowbit(b);
                        b -= d, c += d;
                        b++;
                    } else {
                        if (~b & 1) {
                            b += 1;
                        } else {
                            c += 1;
                        }
                    }
                    for (int i = 1; i <= n - 5; i++) std::cout << 2 << ' ';
                    std::cout << 4 << ' ' << 4 << ' ';
                    std::cout << a << ' ' << b << ' ' << c << '\n';
                }
                return;
            }
        }
    }
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
