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

// segment tree //
struct Info {
    int l, r;
    LL val;
    std::unordered_map<int, int> cnt;

    Info(int _l = 0, int _r = 0, LL _val = 0) : l(_l), r(_r), val(_val) {}

    void add(int col) { cnt[col]++; }
    void del(int col) {
        if (col == 0) return;
        auto it = cnt.find(col);
        if (it->ss == 1) {
            cnt.erase(it);
        } else {
            it->ss--;
        }
    }
};

void solut() {
    int n, q;
    std::cin >> n >> q;

    // segment tree //
    std::vector<Info> tr(4 * n + 1);

    auto build = [&](auto&& self, int u, int l, int r) -> void {
        tr[u] = Info(l, r, 0);
        if (l == r) return;
        int mid = (l + r) >> 1;
        self(self, u << 1, l, mid);
        self(self, u << 1 | 1, mid + 1, r);
    };
    build(build, 1, 1, n);

    auto pushup = [&](int u) { tr[u].val = tr[u << 1].val + tr[u << 1 | 1].val; };

    auto changeCol = [&](auto&& self, int u, int l, int r, int pos, int prev, int now) -> void {
        tr[u].del(prev);
        tr[u].add(now);
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            self(self, u << 1, l, mid, pos, prev, now);
        } else {
            self(self, u << 1 | 1, mid + 1, r, pos, prev, now);
        }
    };

    auto changeVal = [&](auto&& self, int u, int l, int r, int pos, int now) -> void {
        if (l == r) {
            tr[u].val = now;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            self(self, u << 1, l, mid, pos, now);
        } else {
            self(self, u << 1 | 1, mid + 1, r, pos, now);
        }
        pushup(u);
    };

    auto rangeAsk = [&](auto&& self, int u, int l, int r, int ql, int qr) -> LL {
        if (ql <= l and r <= qr) {
            return tr[u].val;
        }
        int mid = (l + r) >> 1;
        LL ans = 0;
        if (ql <= mid) {
            ans += self(self, u << 1, l, mid, ql, qr);
        }
        if (mid < qr) {
            ans += self(self, u << 1 | 1, mid + 1, r, ql, qr);
        }
        return ans;
    };

    auto leAsk = [&](auto&& self, int u, int l, int r, int pos, const vi& have) -> int {
        if (l > pos) return -1;
        if (pos >= r) {
            bool flag = 0;
            for (const auto& [col, _] : tr[u].cnt) {
                if (!have[col]) {
                    flag = 1;
                    break;
                }
            }
            if (!flag) return -1;
            if (l == r) return l;
        }
        int mid = (l + r) >> 1;
        int ans = self(self, u << 1 | 1, mid + 1, r, pos, have);
        if (ans != -1) return ans;
        return self(self, u << 1, l, mid, pos, have);
    };

    auto riAsk = [&](auto&& self, int u, int l, int r, int pos, const vi& have) -> int {
        if (r < pos) return -1;
        if (pos <= l) {
            bool flag = 0;
            for (const auto& [col, _] : tr[u].cnt) {
                if (!have[col]) {
                    flag = 1;
                    break;
                }
            }
            if (!flag) return -1;
            if (l == r) return l;
        }
        int mid = (l + r) >> 1;
        int ans = self(self, u << 1, l, mid, pos, have);
        if (ans != -1) return ans;
        return self(self, u << 1 | 1, mid + 1, r, pos, have);
    };

    vi col(n + 1), val(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> col[i];
        changeCol(changeCol, 1, 1, n, i, 0, col[i]);
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> val[i];
        changeVal(changeVal, 1, 1, n, i, val[i]);
    }

    vi have(n + 1);
    while (q--) {
        int op, p, x, k;
        std::cin >> op;
        if (op == 1) {
            std::cin >> p >> x;
            changeCol(changeCol, 1, 1, n, p, col[p], x);
            col[p] = x;
        } else if (op == 2) {
            std::cin >> p >> x;
            changeVal(changeVal, 1, 1, n, p, x);
            val[p] = x;
        } else {
            std::cin >> x >> k;
            vi temp(k + 1);
            for (int i = 1; i <= k; i++) {
                std::cin >> temp[i];
                have[temp[i]] = 1;
            }
            int l = leAsk(leAsk, 1, 1, n, x, have);
            int r = riAsk(riAsk, 1, 1, n, x, have);
            l = (l == -1 ? 1 : l + 1);
            r = (r == -1 ? n : r - 1);
            std::cout << rangeAsk(rangeAsk, 1, 1, n, l, r) << '\n';
            for (int i = 1; i <= k; i++) {
                have[temp[i]] = 0;
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
