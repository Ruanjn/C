#include <bits/stdc++.h>
#include <iostream>
#define N 110
#define INF 0x7ffffff
using namespace std;

double ans, pos[N];
int n, a[N], r[N], v[N];

void dfs(int t) {
    if (t == n) {
        double low = 0., high = 0.;
        for (int i = 0; i < n; i++) {
            pos[i] = (double)r[a[i]];
            for (int j = 0; j < i; j++) {
                int r1 = r[a[i]], r2 = r[a[j]];
                pos[i] =
                    max(pos[i], pos[j] + sqrt((double)(r1 + r2) * (r1 + r2) -
                                              (r1 - r2) * (r1 - r2)));
            }
            low = min(low, pos[i] - r[a[i]]);
            high = max(high, pos[i] + r[a[i]]);
        }
        ans = min(ans, high - low);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!v[i]) {
            v[i] = 1, a[t] = i;
            dfs(t + 1);
            v[i] = 0;
        }
    }
}

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++)
            scanf("%d", &r[i]);
        ans = INF;
        dfs(0);
        cout << ans << endl;
    }
    system("pause");
    return 0;
}