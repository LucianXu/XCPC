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

tandu struct pnt {
    T x, y;

    pnt(T _x = 0, T _y = 0) { x = _x, y = _y; }

    pnt operator+(const pnt& a) const { return pnt(x + a.x, y + a.y); }

    pnt operator-(const pnt& a) const { return pnt(x - a.x, y - a.y); }

    /*
    bool operator<(const pnt& a) const {
        if (std::is_same<T, double>::value) {
            if (fabs(x - a.x) < eps) return y < a.y;
        } else {
            if (x == a.x) return y < a.y;
        }
        return x < a.x;
    }
    */

    // 注意数乘会不会爆 int //
    pnt operator*(const T k) const { return pnt(k * x, k * y); }

    U operator*(const pnt& a) const { return (U) x * a.x + (U) y * a.y; }

    U operator^(const pnt& a) const { return (U) x * a.y - (U) y * a.x; }

    friend U dist(const pnt& a, const pnt& b) {
        return ((U) a.x - b.x) * ((U) a.x - b.x) + ((U) a.y - b.y) * ((U) a.y - b.y);
    }

    U len() { return dist(pnt(0, 0)); }

    // a, b, c 成逆时针 //
    friend U area(pnt a, pnt b, pnt c) { return (b - a) ^ (c - a); }

    // 两向量夹角，返回 cos 值 //
    double get_angle(pnt a) {
        return (double) (pnt(x, y) * a) / sqrt((double) pnt(x, y).len() * (double) a.len());
    }
};
typedef pnt<int, LL> point;

void solut() {
    int n;
    std::cin >> n;
    std::vector<point> convex(n);
    for (int i = 0; i < n; i++) std::cin >> convex[i].x >> convex[i].y;

    vvl f(n, vl(n));    // dp  f[i][j]: 点 i 与点 j 连线右侧部分的直径 //
    vvl dis(n, vl(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dis[i][j] = dist(convex[i], convex[j]);
        }
        f[i][(i + 1) % n] = dis[i][(i + 1) % n];
    }
    for (int k = 2; k <= n - 1; k++) {
        for (int i = 0, j; i < n; i++) {
            j = (i + k) % n;
            f[i][j] = std::max({f[(i + 1) % n][j], f[i][(j + n - 1) % n], dis[i][j]});
        }
    }

    LL ans = 4 * INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (((convex[i] - convex[(i + 1) % n]) ^ (convex[i] - convex[j])) == 0) {
                continue;
            } else if (((convex[i] - convex[(i + n - 1) % n]) ^ (convex[i] - convex[j])) == 0) {
                continue;
            } else {
                Min(ans, f[i][j] + f[j][i]);
            }
        }
    }
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
