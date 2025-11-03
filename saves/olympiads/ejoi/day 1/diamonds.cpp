#include "diamonds.h"

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<pair<int,int>>> connections;
int two = -1;
int k;

int dfs(int i, int dist)
{
    if(dist >= k) return dist;
    int best = INT_MIN;
    for(int j = 0; j < connections[i].size(); j++)
    {
        if(connections[i][j].second == 2)
        {
            if(two == -1)
                two = dist;
            else
                two = min(two, dist);

        }
        best = max(best, dfs(connections[i][j].first, dist+1));
    }
    return best;
}

long long int calculate_diamonds (int N, int M, int K, std::vector <int> u, std::vector <int> v, std::vector <int> d)
{
    int two1;
    k = K;
    connections.assign(N, vector<pair<int,int>>());
    for(int i = M-1; i >= 0; i--)
    {
        connections[u[i]].push_back({v[i], d[i]});
        if(d[i] == 2)
            two1 = v[i];
        v.resize(i);
        u.resize(i);
        d.resize(i);

    }
    int temp = dfs(two1, 1);
    if(temp < K)
    {
        return K;
    }
    if(two == -1)
    {
        return K+1;
    }
    else
    {
        return (((K-1)/two)+1)*2+(K-(((K-1)/two)+1));
    }
}
