#include <bits/stdc++.h>
#define ll long long
using namespace std;
int t, s = 0;
int main() {
    // freopen("bai1.inp", "r", stdin);
    // freopen("bai1.out", "w", stdout);
    cin >> t;
    while (t--) {
        int m, n;
        cin >> m >> n;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int x;
                cin >> x;
                s += x;
            }
        }
        cout << s << endl;
    }
}