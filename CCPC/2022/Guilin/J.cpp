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
    vi a(n + 1), st(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        st[a[i]] = 1;
    }

    vvi e(n + 1), g(n + 1);
    vi l(n + 1, 1), r(n + 1, n);
    for (int i = 1, u, v; i <= m; i++) {
        std::cin >> u >> v;
        // p_u < p_v: e (u <- v), g (u -> v) //
        e[v].push_back(u);
        g[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (a[i]) {
            l[i] = a[i];
            r[i] = a[i];
        }
    }

    // 正向拓排确定下界 //
    auto top_sort1 = [&]() -> bool {
        vi top, d(n + 1);
        std::queue<int> q;
        for (int i = 1; i <= n; i++) {
            d[i] = e[i].size();
            if (!d[i]) q.push(i);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            top.push_back(u);
            for (const auto& v : g[u]) {
                d[v]--;
                if (!d[v]) q.push(v);
            }
        }
        if (top.size() != n) return false;
        for (const auto& u : top) {
            for (const auto& v : e[u]) Max(l[u], l[v] + 1);
        }
        return true;
    };
    top_sort1();

    // 反向拓排确定上界 //
    auto top_sort2 = [&]() -> bool {
        vi top, d(n + 1);
        std::queue<int> q;
        for (int i = 1; i <= n; i++) {
            d[i] = g[i].size();
            if (!d[i]) q.push(i);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            top.push_back(u);
            for (const auto& v : e[u]) {
                d[v]--;
                if (!d[v]) q.push(v);
            }
        }
        if (top.size() != n) return false;
        for (const auto& u : top) {
            for (const auto& v : g[u]) Min(r[u], r[v] - 1);
        }
        return true;
    };
    top_sort2();
    debug(l, r);


    // 贪心 //
    std::vector<std::tuple<int, int, int>> v;
    for (int i = 1; i <= n; i++) {
        v.emplace_back(r[i], l[i], i);
    }

    std::sort(all(v), [&](std::tuple<int, int, int> a, std::tuple<int, int, int> b) {
        auto [r1, l1, id1] = a;
        auto [r2, l2, id2] = b;
        if (l1 == l2 and r1 == r2) return id1 < id2;
        if (l1 == l2) return r1 < r2;
        return l1 < l2;
    });

    std::priority_queue<
        std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>,
        std::greater<std::tuple<int, int, int>>>
        q;
    for (int i = 1, id = 0; i <= n; i++) {
        while (id < (int) v.size() and std::get<1>(v[id]) <= i) {
            q.push(v[id]);
            id++;
        }
        if (q.empty()) {
            std::cout << "-1" << '\n';
            return;
        }
        auto [r, l, idx] = q.top();
        q.pop();
        if (r < i) {
            std::cout << "-1" << '\n';
            return;
        }
        a[idx] = i;
    }

    for (int i = 1; i <= n; i++) std::cout << a[i] << ' ';
    std::cout << '\n';

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
