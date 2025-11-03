#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
vector<ll> w;
vector<vector<int>> ch;
vector<int> pathMasks;
vector<ll> pathVals;

void genPaths(int u, int mask, ll mn, ll mx)
{
pathMasks.push_back(mask);
pathVals.push_back(mx-mn);
for(int v : ch[u])
{
genPaths(v, mask | (1 << (v-1)), min(mn, w[v]), max(mx, w[v]));
}
}

int main() {
scanf("%d", &n);
w.assign(n+1, 0);
ch.assign(n+1, {});
for(int i = 1; i <= n; i++)
{
scanf("%lld", &w[i]);
}
for(int i = 0; i < n-1; i++)
{
int u,v;
scanf("%d %d", &u, &v);
ch[u].push_back(v);
}
pathMasks.clear();
pathVals.clear();
for(int s = 1; s <= n; s++)
{
genPaths(s, 1 << (s-1), w[s], w[s]);
}
int FULL = 1 << n;
const ll NEG = LLONG_MIN/4;
vector<ll> dp(FULL, NEG);
dp[0] = 0;
for(int mask = 1; mask < FULL; mask++)
{
for(size_t i = 0; i < pathMasks.size(); i++)
{
int p = pathMasks[i];
if((mask & p) == p)
{
dp[mask] = max(dp[mask], dp[mask ^ p] + pathVals[i]);
}
}
}
printf("%lld\n", dp[FULL-1]);
return 0;
}