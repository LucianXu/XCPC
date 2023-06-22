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
    int n, m, k;
    std::cin >> n >> m >> k;
    LL start = 0;
    for (int i = 1, x, y; i <= k; i++) {
        std::cin >> x >> y;
        x--, y--;
        start |= 1ll << (x * m + y);
    }

    int ans = inf;
    auto dfs = [&](auto&& self, LL st) -> void {
        vvi a(n, vi(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (st & (1ll << (i * m + j))) {
                    a[i][j] = 1;
                }
            }
        }
        int move = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j >= 2 and a[i][j] and a[i][j - 1] and !a[i][j - 2]) {    // left //
                    move = 1;
                    LL now = st;
                    now -= (1ll << (i * m + j));
                    now -= (1ll << (i * m + j - 1));
                    now += (1ll << (i * m + j - 2));
                    self(self, now);
                }
                if (j <= m - 3 and a[i][j] and a[i][j + 1] and !a[i][j + 2]) {    // right //
                    move = 1;
                    LL now = st;
                    now -= (1ll << (i * m + j));
                    now -= (1ll << (i * m + j + 1));
                    now += (1ll << (i * m + j + 2));
                    self(self, now);
                }
                if (i >= 2 and a[i][j] and a[i - 1][j] and !a[i - 2][j]) {    // up //
                    move = 1;
                    LL now = st;
                    now -= (1ll << (i * m + j));
                    now -= (1ll << ((i - 1) * m + j));
                    now += (1ll << ((i - 2) * m + j));
                    self(self, now);
                }
                if (i <= n - 3 and a[i][j] and a[i + 1][j] and !a[i + 2][j]) {    // right //
                    move = 1;
                    LL now = st;
                    now -= (1ll << (i * m + j));
                    now -= (1ll << ((i + 1) * m + j));
                    now += (1ll << ((i + 2) * m + j));
                    self(self, now);
                }
            }
        }
        if (!move) {
            int res = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (st & (1ll << (i * m + j))) {
                        res++;
                    }
                }
            }
            Min(ans, res);
            return;
        }
    };

    dfs(dfs, start);
    std::cout << ans << '\n';
    return;
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
