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

struct Info {
    std::array<int, 26> ch = {};
    int cnt, size;

    Info(int _cnt = 0, int _size = 0) : cnt(_cnt), size(_size) { ch = {}; }
};

void solut() {
    int n, k;
    std::cin >> n >> k;

    // trie //
    int idx = 0;
    std::vector<Info> tr = {Info(0, 0)};

    auto newNode = [&]() -> int {
        tr.push_back(Info(0, 0));
        return ++idx;
    };

    auto insert = [&](const std::string& s) {
        int p = 0;
        for (const auto& c : s) {
            if (!tr[p].ch[c - 'a']) tr[p].ch[c - 'a'] = newNode();
            p = tr[p].ch[c - 'a'];
            tr[p].cnt++;
        }
        tr[p].size++;
    };

    for (int i = 1; i <= n; i++) {
        std::string s;
        std::cin >> s;
        insert(s);
    }

    std::string ans = "";
    auto solve = [&](auto&& self, int p, int k) -> void {
        int sum = tr[p].size;
        for (int i = 0; i < 26; i++) {
            if (tr[p].ch[i]) sum++;
        }
        if (sum >= k) return;
        for (int i = 0; i < 26; i++) {
            if (tr[p].ch[i]) {
                sum += tr[tr[p].ch[i]].cnt - 1;
                if (sum >= k) {
                    ans += char(i + 'a');
                    self(self, tr[p].ch[i], k - sum + tr[tr[p].ch[i]].cnt);
                    return;
                }
            }
        }
    };

    solve(solve, 0, k);
    std::cout << (ans.empty() ? "EMPTY" : ans) << '\n';

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
