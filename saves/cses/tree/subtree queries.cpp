#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<ll>> connections;
vector<ll> val, flat, seg, inn, out;
ll timer = 0, amount;

void build()
{
    for(ll i = amount-1; i > 0; i--)
    {
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }
}

void modify(ll pos, ll val)
{
    pos += amount;
    for(seg[pos] = val; pos > 1; pos >>= 1)
    {
        seg[pos >> 1] = seg[pos] + seg[pos ^ 1];
    }
}

ll pref(ll pos) {
    ll res = 0;
    ll l = amount;
    ll r = pos + amount + 1;
    while (l < r) {
        if (l & 1) res += seg[l++];
        if (r & 1) res += seg[--r];
        l >>= 1; r >>= 1;
    }
    return res;
}

void dfs(ll i, ll p)
{
    inn[i] = timer++;
    flat[timer-1] = val[i];
    for(ll j = 0; j < connections[i].size(); j++)
    {
        if(connections[i][j] != p)
        {  
            dfs(connections[i][j], i);
        }
    }
    out[i] = timer;
}

int main() 
{
    ll amountq, temp, temp2;
    scanf("%lld %lld", &amount, &amountq);
    val.assign(amount, -1);
    for(ll i = 0; i < amount; i++)
    {
        scanf("%lld", &val[i]);
    }
    connections.assign(amount, vector<ll>());
    for(ll i = 0; i < amount-1; i++)
    {
        scanf("%lld %lld", &temp, &temp2);
        temp--;
        temp2--;
        connections[temp].push_back(temp2);
        connections[temp2].push_back(temp);
    }
    inn.assign(amount, 0);
    out.assign(amount, 0);
    flat.assign(amount, -1);
    dfs(0, -1);
    seg.resize(amount*2);
    for (ll i = 0; i < amount; i++)
        seg[amount + i] = flat[i];
    build();
    ll type, idx, setto;
    while(amountq--)
    {
        scanf("%lld %lld", &type, &idx);
        idx--;
        if(type == 1)
        {
            scanf("%lld", &setto);
            modify(inn[idx], setto);
        }
        else
        {
            printf("%lld\n", pref(out[idx]-1) - pref(inn[idx]-1));
        }
    }
}