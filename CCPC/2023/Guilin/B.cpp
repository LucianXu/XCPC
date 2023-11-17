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
    vi a(n + 1), b(m + 1);
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= m; i++) std::cin >> b[i];
    while (b.size() < a.size()) b.push_back(0);
    std::sort(all(a));
    std::sort(all(b));
    LL add = 0, sub = n - m;
    for (int i = n - m + 1; i <= n; i++) {
        if (b[i] < a[i]) {
            std::cout << -1 << '\n';
            return;
        } else {
            add += b[i] - a[i];
        }
    }
    if (add > sub) {
        std::cout << -1 << '\n';
        return;
    }
    vi ans;
    for (int i = 1; i <= n - m and add < sub; i++) {
        auto p = std::upper_bound(a.begin() + i, a.end(), a[i]) - a.begin() - 1;
        ans.push_back(a[p]);
        a[p]++;
        if (p <= n - m) add++;
        if (p > n - m and a[p] > b[p]) {
            std::cout << -1 << '\n';
            return;
        }
    }
    for (int i = n - m + 1; i <= n; i++) {
        for (int j = a[i]; j < b[i]; j++) ans.push_back(j);
    }
    std::cout << ans.size() << '\n';
    for (const auto& x : ans) std::cout << x << ' ';
    std::cout << '\n';
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

