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
    vi a(n), b(n);
    for (int i = 0; i < n; i++) std::cin >> a[i];
    b = a;
    LL res = 0;

    vi tmp(n);
    auto solve = [&](auto&& self, int l, int r) -> void {
        if (l == r) return;
        int mid = (l + r) / 2;
        self(self, l, mid), self(self, mid + 1, r);
        int ll = l, rr = mid + 1, id = l;
        while (ll <= mid and rr <= r) {
            if (a[ll] <= a[rr]) {
                tmp[id++] = a[ll++];
            } else {
                tmp[id++] = a[rr++];
                res += 1ll * mid + 1 - ll;
            }
        }
        while (ll <= mid) tmp[id++] = a[ll++];
        while (rr <= r) tmp[id++] = a[rr++];
        for (int i = l; i <= r; i++) a[i] = tmp[i];
    };

    solve(solve, 0, n - 1);
    std::cout << res << '\n';
    LL sum = 1ll * n * (n - 1) / 2;
    int st = 0, en = n - 1, rev = 1;
    while (m--) {
        char ch;
        std::cin >> ch;
        if (ch == 'S') {
            if (rev == 1) {
                res += 1ll * n + 1 - 2 * b[st];
                st = (st + 1 + n) % n;
                en = (en + 1 + n) % n;
            } else {
                res += 1ll * n + 1 - 2 * b[st];
                st = (st - 1 + n) % n;
                en = (en - 1 + n) % n;
            }
        } else {
            res = sum - res;
            std::swap(st, en);
            rev *= -1;
        }
        res = (res % 10 + 10) % 10;
        std::cout << res;
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
