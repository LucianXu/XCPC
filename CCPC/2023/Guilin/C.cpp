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
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

#ifdef LOCAL
#include "../debug.h"
#else
#define debug(...) \
    do {           \
    } while (false)
#endif

constexpr int mod = 998244353;
constexpr int power(int a, int n) {
    int ans = 1;
    while (n) {
        debug(n);
        if (n & 1) ans = 1ll * ans * a % mod;
        a = 1ll * a * a % mod;
        n >>= 1;
    }
    return ans;
}

void solut() {
    int n;
    std::cin >> n;
    vi a(n + 1), b = {0}, cnt(n + 1);
    cnt[0] = 1;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        b.push_back(a[i]);
        cnt[a[i]]++;
    }
    std::sort(all(b));
    b.erase(unique(all(b)), b.end());
    int ans = 0;
    for (int i = 0; i < b.size(); i++) {
        vi v;
        for (int j = 1; j * j <= b[i]; j++) {
            if (b[i] % j) continue;
            if (b[i] != j and cnt[j]) v.push_back(j);
            if (b[i] != b[i] / j and j * j != b[i] and cnt[b[i] / j]) {
                v.push_back(b[i] / j);
            }
        }
        if (i == 0) {
            for (int j = 1; j <= n; j++)
                if (cnt[j]) v.push_back(j);
        }
        /* linear basis */
        const int M = 20;
        vi lb(M);
        auto insert = [&](int x) {
            for (int i = M - 1; ~i and x; i--) {
                if (x >> i & 1) {
                    if (lb[i]) {
                        x ^= lb[i];
                    } else {
                        return lb[i] = x, true;
                    }
                }
            }
            return false;
        };
        auto cacl = [&](const vi& a) {
            int res = 0;
            for (const auto& x : a) {
                res += cnt[x];
                if (insert(x)) res--;
            }
            std::fill(all(lb), 0);
            return res;
        };
        /* end linear basis*/
        LL res = power(2, cnt[b[i]] - 1 + cacl(v));
        ans = (ans + res) % mod;
    }
    std::cout << (ans == 0 ? mod - 1 : ans - 1) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int t = 1;
    std::cin >> t;
    while (t--) {
        solut();
    }
    return 0;
}

