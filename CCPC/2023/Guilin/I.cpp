#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using i128 = __int128;
using PII = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vl = std::vector<LL>;
using vvl = std::vector<vl>;
using vpi = std::vector<PII>;

#define ff first
#define ss second
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(), x.rend()

#ifdef LOCAL
#include "../debug.h"
#else
#define debug(...) \
    do{            \
    } while (false)
#endif
const int N = 5e5 + 9;
int a[N], las[N], t[N];
void solut() {
    int n, m;
    cin >> n >> m;
    auto ins = [&](int x, int k) {
        for (; x <= n; x += x & -x) t[x] += k;
    };
    auto ask = [&](int x) {
        int z = 0;
        for (; x; x ^= x & -x) z += t[x];
        return z;
    };
    auto qry = [&](int l, int r) {
        // debug(l, r, l > r ? 0 : ask(r) - ask(l - 1));
        return l > r ? 0 : ask(r) - ask(l - 1);
    };
    int z = -1;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        z = max(z, qry(las[a[i]] + 1, i - 1) - a[i]);
        if (las[a[i]]) ins(las[a[i]], -1);
        ins(i, 1), las[a[i]] = i;
    }
    int v = 1;
    while (las[v]) ++v;
    z = max(z, qry(1, n) - v);
    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        z = max(z, qry(las[x] + 1, n) - x);
    }
    cout << z << '\n';
    for (int i = 1; i <= n; ++i) las[a[i]] = 0;
    memset(t, 0, n + 1 << 2);
}

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    int t = 1;
    std::cin >> t;
    while (t --) {
        solut();
    }
    return 0;
}
