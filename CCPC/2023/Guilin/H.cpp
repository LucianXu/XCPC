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
    int n, k;
    std::cin >> n >> k;
    vi a(n + 1);
    vvi e(n + 1);
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1, u, v; i < n; i++) {
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    std::vector<std::array<int, 3>> f(n + 1);
    /* [maximal even value, maximal odd value, answer] */
    auto dfs = [&](auto&& self, int u, int fa) -> void {
        int ans = 0;
        std::array<int, 2> g = {}; /* even, odd */
        if (a[u] == 1) {
            g = {-inf, 1};
        } else {
            g = {a[u], -inf};
        }
        for (const auto& v : e[u]) {
            if (v == fa) continue;
            self(self, v, u);
            ans += f[v][2];
            auto h = g;
            g[0] = std::max({h[0], h[0] + f[v][0], h[1] + f[v][1]});
            g[1] = std::max({h[1], h[0] + f[v][1], h[1] + f[v][0]});
        }
        if (g[k & 1] >= k) {
            f[u] = {-inf, -inf, ans + 1};
        } else {
            f[u] = {g[0], g[1], ans};
        }
    };
    dfs(dfs, 1, 0);
    std::cout << f[1][2] << '\n';
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

