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

void solut() {
    string s;
    cin >> s;
    string tmp;
    int sum = 0;
    for (int i = 0; i < s.size(); i ++) {
        if (s[i] == '(') {
            tmp += '(';
            sum ++;
        } else {
            tmp += ')';
            sum --;
            sum = max(0, sum);
        }
    }
    if (sum == 0) {
        cout << s << '\n';
    } else {
        cout << "impossible" << '\n';
    }
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
