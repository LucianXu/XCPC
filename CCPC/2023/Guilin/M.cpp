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

const int N = 3e5 + 9;
int a[N], b[N], d[N], u[N], v[N], f[N], g[N];
void solut() {
    int n;
    cin >> n;
    basic_string<int> vec;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i];
        vec += a[i], vec += b[i];
    }
    sort(all(vec));
    vec.erase(unique(all(vec)),end(vec));
    auto chk = [&](int k) {
        for (int i = 1; i <= n; ++i) {
            u[i] = a[i] < k ? -1 : 1;
            v[i] = b[i] < k ? -1 : 1;
            d[i] = v[i] - u[i];
        }
        g[0] = -1;
        for (int i = 1; i <= n; ++i) {
            if (f[i - 1] >= 0) {
                f[i] = f[i - 1] + d[i];
                g[i] = g[i - 1];
            } else {
                f[i] = d[i];
                g[i] = i - 1;
            }
        }
        int r = max_element(f, f + n + 1) - f;
        int l = g[r] + 1, sum = 0;
        for (int i = 1; i <= n; ++i) {
            sum += l <= i && i <= r ? v[i] : u[i];
        }
        return sum >= 0;
    };
    int l = 0, r = vec.size();
    while (l < r) {
        int md = l + r >> 1;
        if (chk(vec[md])) l = md + 1; else r = md;
    }
    cout << vec[r - 1] << '\n';
}

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    int t = 1;
    // std::cin >> t;
    while (t --) {
        solut();
    }
    return 0;
}
