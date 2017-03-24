#include <bits/stdc++.h>

using namespace std;

#define lol long long
#define fi first
#define se second
#define pb push_back
#define sz(s) (int)s.size()
#define must ios_base::sync_with_stdio(0)

#define inp(s) freopen(s, "r", stdin)
#define out(s) freopen(s, "w", stdout)

const int N = 2010;
const int M = 5010;
const int64_t inf = (lol)4e+18 - 1e+16;
pair<pair<int, int>, int64_t> e[M];
int64_t d[N];

int main()
{

//    cout << inf + (lol)2e+15 << "\n";
//    return 0;
//    inp("input.txt");
    inp("path.in");
    out("path.out");
    int n, m, s, i, j;
    scanf("%d%d%d", &n, &m, &s);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d%I64d", &e[i].fi.fi, &e[i].fi.se, &e[i].se);
    }
    fill(d, d + N, inf);
    d[s] = 0;
    for (i = 1; i < n; i++)
        for (j = 1; j <= m; j++)
            if (d[e[j].fi.fi] != inf && d[e[j].fi.fi] + e[j].se < d[e[j].fi.se])
            {
                d[e[j].fi.se] = max(-inf, d[e[j].fi.fi] + e[j].se);
            }

    for (i = 1; i < n; i++)
        for (j = 1; j <= m; j++)
            if (d[e[j].fi.fi] != inf && d[e[j].fi.fi] + e[j].se < d[e[j].fi.se])
            {
                d[e[j].fi.se] = -inf;
            }

    for (i = 1; i <= n; i++)
    {
        if (d[i] <= -inf)
        {
            printf("-\n");
        }
        else if (d[i] == inf)
        {
            printf("*\n");
        }
        else
        {
            printf("%I64d\n", d[i]);
        }
    }
    return 0;
}
