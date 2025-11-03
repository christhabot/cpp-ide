#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<ll>> connections1;
vector<vector<ll>> connections2;
vector<bool> explored;

ll bfs1(bool second)
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
        if(!second)
        {
            for(int i = 0; i < connections1[idx].size(); i++)
            {
                if(!explored[connections1[idx][i]])
                {
                    q.push(connections1[idx][i]);
                }
            }
        }
        else
        {
            for(int i = 0; i < connections2[idx].size(); i++)
            {
                if(!explored[connections2[idx][i]])
                {
                    q.push(connections2[idx][i]);
                }
            }
        }
    }
    return last;
}

ll bfs2(ll j, bool second)
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
        if(!second)
        {
            for(int i = 0; i < connections1[idx.first].size(); i++)
            {
                if(!explored[connections1[idx.first][i]])
                {
                    q.push({connections1[idx.first][i], idx.second+1});
                }
            }
        }
        else
        {
            for(int i = 0; i < connections2[idx.first].size(); i++)
            {
                if(!explored[connections2[idx.first][i]])
                {
                    q.push({connections2[idx.first][i], idx.second+1});
                }
            }
        }
    }
    return last.second;
}

int main() {
    ll amount1, amount2;
    ll temp, temp2;
    ll dist1, dist2;

    scanf("%lld", &amount1);
    connections1.assign(amount1, vector<ll>());
    for(int i = 0; i < amount1-1; i++)
    {
        scanf("%lld %lld", &temp, &temp2);
        temp--;
        temp2--;
        connections1[temp].push_back(temp2);
        connections1[temp2].push_back(temp);
    }

    scanf("%lld", &amount2);
    connections2.assign(amount2, vector<ll>());
    for(int i = 0; i < amount2-1; i++)
    {
        scanf("%lld %lld", &temp, &temp2);
        temp--;
        temp2--;
        connections2[temp].push_back(temp2);
        connections2[temp2].push_back(temp);
    }

    explored.assign(amount1, false);
    temp = bfs1(false);
    explored.assign(amount1, false);
    dist1 = bfs2(temp, false);

    explored.assign(amount2, false);
    temp = bfs1(true);
    explored.assign(amount2, false);
    dist2 = bfs2(temp, true);
    printf("%lld", max(dist1, max(dist2, (dist1+1)/2+(dist2+1)/2+1)));
    return 0;
}