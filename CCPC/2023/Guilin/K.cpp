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
const int N = 2e6;
vector<int> vec[N];
void solut() {
    int n, m;
    cin >> m >> n;
    vector a(n, vector(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int& x : a[i]) cin >> x, --x;
    }
    int c = 0;
    vector<int> iot(m);
    iota(all(iot), 0);
    int fl = 1;
    vec[0] = iot, c = 1;
    for (int i = 0; i < n; ++i) {
        int h = c;
        for (int x = 0; x < h; ++x) {
            auto p = vec[x], q = p;
            for (int j = 0; j < m; ++j) p[j] = q[a[i][j]];
            vec[c++] = p;
            if (p == iot) fl = 0;
        }
        sort(vec, vec + c);
        c = unique(vec, vec + c) - vec;
    }
    cout << c - fl << '\n';
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
