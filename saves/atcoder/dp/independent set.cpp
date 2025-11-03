#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<ll>> connections;

ll mod = 1e9 + 7;

pair<ll,ll> dfs(int u, int parent) {
    ll white = 1, black = 1;
    for (int v : connections[u]) {
        if (v == parent) continue;
        auto [w, b] = dfs(v, u);
        white = white * ((w + b) % mod) % mod;
        black = black * w % mod;
    }
    return {white, black};
}

int main() {
    ll amount, temp, temp2;
    scanf("%lld", &amount);
    connections.assign(amount, vector<ll>());
    for(int i = 0; i < amount-1; i++)
    {
        scanf("%lld %lld", &temp, &temp2);
        temp--;
        temp2--;
        connections[temp].push_back(temp2);
        connections[temp2].push_back(temp);
    }
    pair<ll,ll> tempp;
    tempp = dfs(0,0);
    printf("%lld", (tempp.first + tempp.second) % mod);
}