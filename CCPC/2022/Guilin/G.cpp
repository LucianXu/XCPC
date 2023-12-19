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
    int n;
    std::cin >> n;
    vi w(n + 1);
    vvi e(n + 1);
    for (int i = 1; i <= n; i++) std::cin >> w[i];
    for (int i = 1, u, v; i < n; i++) {
        std::cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    if (n == 1) {
        std::cout << "0" << '\n';
        return;
    }

    int ans = 0;

    // dfs1: 处理出子树中最长的四条链 //
    std::vector<std::array<int, 4>> chain(n + 1, {0, 0, 0, 0});
    auto dfs1 = [&](auto&& self, int u, int fa) -> void {
        vi tmp;
        for (const auto& v : e[u]) {
            if (v == fa) continue;
            self(self, v, u);
            tmp.push_back(chain[v][0] + w[u]);
        }
        if (tmp.empty()) {
            chain[u][0] = w[u];
        } else {
            std::sort(rall(tmp));
            tmp.resize(4, 0);
            for (int i = 0; i < 4; i++) chain[u][i] = tmp[i];
        }
        return;
    };
    dfs1(dfs1, 1, 0);

    // dfs2: 换根处理来着父亲的最长链 //
    vi chain_fa(n + 1);
    auto dfs2 = [&](auto&& self, int u, int fa) -> void {
        std::set<PII> from_u;
        for (const auto& v : e[u]) {
            if (v == fa) continue;
            from_u.emplace(chain[v][0], v);
        }
        for (const auto& v : e[u]) {
            if (v == fa) continue;
            from_u.erase({chain[v][0], v});
            if (from_u.empty()) {
                chain_fa[v] = chain_fa[u] + w[v];
            } else {
                chain_fa[v] = std::max(chain_fa[u], from_u.rbegin()->ff + w[u]) + w[v];
            }
            from_u.emplace(chain[v][0], v);
            self(self, v, u);
        }
        int res = 0;
        vi tmp;
        tmp.push_back(chain[u][0]);
        tmp.push_back(chain[u][1]);
        tmp.push_back(chain[u][2]);
        tmp.push_back(chain[u][3]);
        tmp.push_back(chain_fa[u]);
        std::sort(rall(tmp));
        for (int i = 0; i < 4; i++) {
            if (tmp[i]) res += tmp[i] - w[u];
        }
        Max(ans, res);
        return;
    };
    chain_fa[1] = w[1];
    dfs2(dfs2, 1, 0);

    // dfs3: 处理出子树的直径和最长链 (其实在 dfs1 就能一起处理) //
    vi dia(n + 1);        // 直径 //
    vi longest(n + 1);    // 最长链 //
    auto dfs3 = [&](auto&& self, int u, int fa) -> void {
        dia[u] = w[u];
        for (const auto& v : e[u]) {
            if (v == fa) continue;
            self(self, v, u);
            Max(dia[u], dia[v]);
        }
        Max(dia[u], chain[u][0] + chain[u][1] - (chain[u][1] ? w[u] : 0));
        longest[u] = chain[u][0];
        return;
    };
    dfs3(dfs3, 1, 0);

    // dfs4: 换根处理两个不相交链的最大值 //
    auto dfs4 = [&](auto&& self, int u, int fa, int best, int lgst) -> void {
        Max(ans, dia[u] + best);
        std::set<PII> best_set = {{best, -1}};
        std::set<PII> longest_set = {{lgst, -1}};
        for (const auto& v : e[u]) {
            if (v == fa) continue;
            best_set.emplace(dia[v], v);
            longest_set.emplace(longest[v], v);
        }
        for (const auto& v : e[u]) {
            if (v == fa) continue;
            best_set.erase({dia[v], v});
            longest_set.erase({longest[v], v});
            int case1 = best_set.empty() ? 0 : best_set.rbegin()->ff;
            int case2 = w[u];
            auto it = longest_set.end();
            if ((int) longest_set.size() > 0) {
                --it;
                case2 += it->ff;
            }
            if ((int) longest_set.size() > 1) {
                --it;
                case2 += it->ff;
            }
            self(self, v, u, std::max(case1, case2), longest_set.rbegin()->ff + w[u]);
            best_set.emplace(dia[v], v);
            longest_set.emplace(longest[v], v);
        }
        return;
    };
    dfs4(dfs4, 1, 0, 0, 0);

    std::cout << ans << '\n';
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
