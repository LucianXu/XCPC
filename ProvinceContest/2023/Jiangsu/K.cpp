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

template <int P>
struct Mint {
    int v = 0;

    // reflection
    template <typet = int>
    constexpr operator T() const {
        return v;
    }

    // constructor //
    constexpr Mint() = default;
    template <typet>
    constexpr Mint(T x) : v(x % P) {}

    // io //
    friend std::istream& operator>>(std::istream& is, Mint& x) {
        LL y;
        is >> y;
        x = y;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Mint x) { return os << x.v; }

    // comparision //
    friend constexpr bool operator==(Mint lhs, Mint rhs) { return lhs.v == rhs.v; }
    friend constexpr bool operator!=(Mint lhs, Mint rhs) { return lhs.v != rhs.v; }
    friend constexpr bool operator<(Mint lhs, Mint rhs) { return lhs.v < rhs.v; }
    friend constexpr bool operator<=(Mint lhs, Mint rhs) { return lhs.v <= rhs.v; }
    friend constexpr bool operator>(Mint lhs, Mint rhs) { return lhs.v > rhs.v; }
    friend constexpr bool operator>=(Mint lhs, Mint rhs) { return lhs.v >= rhs.v; }

    // arithmetic //
    friend constexpr Mint operator+(Mint lhs, Mint rhs) {
        return lhs.v + rhs.v <= P ? lhs.v + rhs.v : lhs.v - P + rhs.v;
    }
    friend constexpr Mint operator-(Mint lhs, Mint rhs) {
        return lhs.v < rhs.v ? lhs.v + P - rhs.v : lhs.v - rhs.v;
    }
    friend constexpr Mint operator*(Mint lhs, Mint rhs) {
        return static_cast<LL>(lhs.v) * rhs.v % P;
    }
    constexpr Mint operator+=(Mint rhs) { return v = v + rhs; }
    constexpr Mint operator-=(Mint rhs) { return v = v - rhs; }
    constexpr Mint operator*=(Mint rhs) { return v = v * rhs; }
    friend constexpr Mint operator&(Mint lhs, Mint rhs) { return lhs.v & rhs.v; }
    friend constexpr Mint operator|(Mint lhs, Mint rhs) { return lhs.v | rhs.v; }
    friend constexpr Mint operator^(Mint lhs, Mint rhs) { return lhs.v ^ rhs.v; }
    friend constexpr Mint operator>>(Mint lhs, Mint rhs) { return lhs.v >> rhs.v; }
    friend constexpr Mint operator<<(Mint lhs, Mint rhs) { return lhs.v << rhs.v; }
    constexpr Mint operator&=(Mint rhs) { return v = v & rhs; }
    constexpr Mint operator|=(Mint rhs) { return v = v | rhs; }
    constexpr Mint operator^=(Mint rhs) { return v = v ^ rhs; }
    constexpr Mint operator>>=(Mint rhs) { return v = v >> rhs; }
    constexpr Mint operator<<=(Mint rhs) { return v = v << rhs; }
    friend constexpr Mint power(Mint a, Mint n) {
        Mint ans = 1;
        while (n) {
            if (n & 1) ans *= a;
            a *= a;
            n >>= 1;
        }
        return ans;
    }
    friend constexpr Mint inv(Mint rhs) { return power(rhs, P - 2); }
    friend constexpr Mint operator/(Mint lhs, Mint rhs) { return lhs * inv(rhs); }
    constexpr Mint operator/=(Mint rhs) { return v = v / rhs; }
};
using Z = Mint<998244353>;

void solut() {
    int n, m, k;
    std::cin >> n >> m >> k;
    if (m >= k) {
        std::cout << "No\n";
        return;
    }
    if (k == 1) {
        if (n > 26) {
            std::cout << "No\n";
            return;
        }
        std::cout << "Yes\n";
        for (int i = 0; i < n; i++) std::cout << char('a' + i) << '\n';
        return;
    }
    if (m == 1) {
        std::cout << "Yes\n";
        int cnt = 0;
        for (int i = 0; cnt < n && i < 26; i++) {
            for (int j = i + 1; cnt < n && j < 26; j++, cnt++) {
                std::string temp = "";
                temp += char('a' + j);
                temp += char('a' + i);
                for (int u = 0, o = 0; u < k; u++, o = (o + 1) % 2) {
                    std::cout << temp[o];
                }
                std::cout << '\n';
            }
        }
        return;
    }
    if (m == 0) {
        if (n > 26) {
            std::cout << "No\n";
            return;
        }
        std::cout << "Yes\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                std::cout << char('a' + i);
            }
            std::cout << '\n';
        }
        return;
    }
    std::cout << "Yes\n";
    int cnt = 0;
    for (int i = 0; cnt < n && i < 26; i++) {
        for (int j = i + 1; cnt < n && j < 26; j++, cnt++) {
            std::string temp = "";
            temp += char('a' + j);
            temp += char('a' + i);
            if (cnt < 2) {
                for (int u = 0; u < m; u++) std::cout << 'a';
                for (int u = m, o = 0; u < k; u++, o = (o + 1) % 2) {
                    std::cout << temp[o];
                }
                std::cout << '\n';
            } else {
                for (int u = 0, o = 0; u < k; u++, o = (o + 1) % 2) {
                    std::cout << temp[o];
                }
                std::cout << '\n';
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int t = 1;
    // std::cin >> t;
    while (t--) {
        solut();
    }
    return 0;
}
