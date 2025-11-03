#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> freq;
vector<vector<ll>> connections;
priority_queue<pair<ll,ll>> pending;
vector<ll> used;
vector<ll> depth;

void dfs(ll i, ll p, ll d)
{
    depth[i] = d;
    for(ll j = 0; j < connections[i].size(); j++)
    {
        if(connections[i][j] != p)
        {
            dfs(connections[i][j], i, d+1);
        }
    }
}

int main()
{
    ll amount, chmax, res, total;
    ll temp, temp2;
    bool line = true, good;
    scanf("%lld %lld", &amount, &chmax);
    freq.resize(amount);
    connections.assign(amount, vector<ll>());
    for(ll i = 0; i < amount; i++)
    {
        scanf("%lld", &freq[i]);
    }
    for(ll i = 0; i < amount-1; i++)
    {
        scanf("%lld %lld", &temp, &temp2);
        temp--;
        temp2--;
        connections[temp].push_back(temp2);
        connections[temp2].push_back(temp);
        if(temp != temp2+1 && temp2 != temp+1)
        {
            line = false;
        }
    }
    // cout << (int(-3) < int(-4));
    if(chmax == 0)
    {
        depth.assign(amount, -1);
        dfs(0, -1, 0);
        for(int i = 0; i < amount; i++)
        {
            if(depth[i] * -1 < freq[i])
            {
                printf("-1");
                return 0;
            }
        }
        printf("0");
    }
    /* else if(chmax > 1000000000)
    {
        depth.assign(amount, -1);
        dfs(0, -1, 0);
        total = 0;
        for(int i = 0; i < amount; i++)
        {
            // total += min(freq[i] + depth[i], 0);
            if(depth[i] * -1 < freq[i])
            {
                printf("-1");
                return 0;
            }
        }
        printf("%lld", total);
    } */
    if(line || true)
    {
        res = 0;
        total = 0;
        used.assign(amount, 0);
        for(ll i = 0; i < amount; i++)
        {
            // cout << res << " " << freq[i] << "\n";
            if(res < freq[i])
            {
                // cout << 'e';
                if(freq[i] - res > chmax)
                {
                    // cout << 'a';
                    used[i] = chmax;
                    pending.push({i, freq[i]-res-chmax});
                }
                else
                {
                    used[i] = freq[i] - res;
                }
                total += freq[i] - res;
                res = freq[i];
                used[i] = max(used[i], 0ll);
            }
            res--;
        }
        good = true;
        pair<ll,ll> tp;
        for(ll i = 0; i < amount; i++)
        {
            if(!pending.empty())
            {
                tp = pending.top();
                // cout << tp.first << " " << tp.second << "\n";
                if(tp.first < i)
                {
                    good = false;
                }
                while(!pending.empty() && tp.second <= chmax - used[i])
                {
                    // cout << tp.first << " " << tp.second << "\n";
                    pending.pop();
                    used[i] += tp.second;
                    if(!pending.empty())
                        tp = pending.top();
                }
                if(!pending.empty())
                {
                    pending.pop();
                    pending.push({tp.first, tp.second - (max(chmax - used[i],0ll))});
                }
            }
        }
        if(pending.empty() && good)
        {
            printf("%lld", total);
        }
        else
        {
            printf("-1");
        }
    }
}
