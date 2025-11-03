#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<pair<int, pair<int,int>>> vec;
vector<ll> dist;

int main() {
    ll nodes, edges;
    ll temp1, temp2, temp3;
    int n1, n2, w;
    scanf("%lld %lld", &nodes, &edges);
    dist.assign(nodes, LLONG_MIN);
    for(ll i = 0; i < edges; i++)
    {
        scanf("%lld %lld %lld", &temp1, &temp2, &temp3);
        temp1--;
        temp2--;
        vec.push_back({temp3,{temp1, temp2}});
    }
    dist[0] = 0;
    for(int rel = 0; rel < nodes; rel++)
    {
        for(int i = 0; i < vec.size(); i++)
        {
            n1 = vec[i].second.first;
            n2 = vec[i].second.second;
            w = vec[i].first;
            if(dist[n1] != LLONG_MIN && dist[n2] < dist[n1] + w)
            {
                if(rel == nodes-1)
                {
                    printf("-1");
                    return 0;
                }

                dist[n2] = dist[n1] + w;
            }
        }
    }
    printf("%lld", dist[nodes-1]);
}