#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<ll>> connections;
vector<bool> explored;

ll bfs1()
{
    ll idx, last;
    queue<ll> q;
    q.push(0);
    while(!q.empty())
    {
        idx = q.front();
        q.pop();
        if(explored[idx])
            continue;
        explored[idx] = true;
        last = idx;
        for(int i = 0; i < connections[idx].size(); i++)
        {
            if(!explored[connections[idx][i]])
            {
                q.push(connections[idx][i]);
            }
        }
    }
    return last;
}

ll bfs2(ll j)
{
    pair<ll,ll> idx, last;
    queue<pair<ll,ll>> q;
    q.push({j,0});
    while(!q.empty())
    {
        idx = q.front();
        q.pop();
        if(explored[idx.first])
            continue;
        explored[idx.first] = true;
        last = idx;
        for(int i = 0; i < connections[idx.first].size(); i++)
        {
            if(!explored[connections[idx.first][i]])
            {
                q.push({connections[idx.first][i], idx.second+1});
            }
        }
    }
    return last.second;
}

int main() {
    ll amount;
    ll temp, temp2;
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
    explored.assign(amount, false);
    temp = bfs1();
    explored.assign(amount, false);
    printf("%lld", bfs2(temp));
    return 0;
}