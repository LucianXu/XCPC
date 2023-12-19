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
    LL val = 0;

    Info(LL _val = INF) : val(_val) {}

    Info operator+(const Info& b) const { return Info(std::min(val, b.val)); }
};

struct Tag {
    LL change = 0;

    Tag(LL _change = 0) : change(_change) {}

    bool operator==(const Tag& b) const { return change == b.change; }
};

void infoApply(Info& a, int l, int r, const Tag& tag) { a.val = tag.change; }

void tagApply(Tag& a, int l, int r, const Tag& tag) { a.change = tag.change; }

template <class Info, class Tag>
class segTree {
#define ls i << 1
#define rs i << 1 | 1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

    int n = 1;
    std::vector<Info> info;
    std::vector<Tag> tag;

   public:
    segTree(const std::vector<Info>& init) : n(init.size() - 1) {
        assert(n > 0);
        info.resize(4 << std::__lg(n));
        tag.resize(4 << std::__lg(n));
        auto build = [&](auto&& dfs, int i, int l, int r) -> void {
            if (l == r) {
                info[i] = init[l];
                return;
            }
            dfs(dfs, lson);
            dfs(dfs, rson);
            push_up(i);
        };
        build(build, 1, 1, n);
    }


   private:
    void push_up(int i) { info[i] = info[ls] + info[rs]; }


    template <class... T>
    void apply(int i, int l, int r, const T&... val) {
        ::infoApply(info[i], l, r, val...);
        ::tagApply(tag[i], l, r, val...);
    }

    void push_down(int i, int l, int r) {
        if (tag[i] == Tag{}) return;
        apply(lson, tag[i]);
        apply(rson, tag[i]);
        tag[i] = {};
    }

   public:
    template <class... T>
    void rangeMerge(int ql, int qr, const T&... val) {
        auto dfs = [&](auto&& dfs, int i, int l, int r) -> void {
            if (qr < l or r < ql) return;
            if (ql <= l and r <= qr) {
                apply(i, l, r, val...);
                return;
            }
            push_down(i, l, r);
            dfs(dfs, lson);
            dfs(dfs, rson);
            push_up(i);
        };
        dfs(dfs, 1, 1, n);
    }

    Info rangeQuery(int ql, int qr) {
        Info res{};
        auto dfs = [&](auto&& dfs, int i, int l, int r) -> void {
            if (qr < l or r < ql) return;
            if (ql <= l and r <= qr) {
                res = res + info[i];
                return;
            }
            push_down(i, l, r);
            dfs(dfs, lson);
            dfs(dfs, rson);
        };
        dfs(dfs, 1, 1, n);
        return res;
    }

#undef rson
#undef lson
#undef mid
#undef rs
#undef ls
};

void solut() {
    int n, m;
    std::cin >> n;
    n++;
    vi a(n + 1);
    for (int i = 1; i < n; i++) std::cin >> a[i];

    // BIT: find p //
    vi p(n + 1);
    auto modityP = [&](int pos, int val) {
        while (pos <= n) {
            Max(p[pos], val);
            pos += lowbit(pos);
        }
    };

    auto queryP = [&](int pos) -> int {
        int ans = 0;
        while (pos) {
            Max(ans, p[pos]);
            pos -= lowbit(pos);
        }
        return ans;
    };

    std::cin >> m;
    for (int i = 1, l, r; i <= m; i++) {
        std::cin >> l >> r;
        modityP(r + 1, l);
    }

    // segment tree: minimal val //
    std::vector<Info> tmp(n + 1, Info(INF));
    tmp[0] = Info(0);
    segTree<Info, Tag> tr(tmp);

    for (int i = 1; i <= n; i++) {
        int l = queryP(i);
        int r = i - 1;
        LL ans = (l == 0 ? 0 : tr.rangeQuery(l, r).val);
        tr.rangeMerge(i, i, Tag(ans + a[i]));
    }
    std::cout << tr.rangeQuery(n, n).val << '\n';
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
