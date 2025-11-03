#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<ll>> dist;

int main() {
    int nodes, edges;
    int temp1, temp2, temp3;
    int amountq;
    scanf("%d %d %d", &nodes, &edges, &amountq);
    dist.assign(nodes, vector<ll>(nodes, -1));
    for(int i = 0; i < nodes; i++)
    {
        dist[i][i] = 0;
    }
    for(int i = 0; i < edges; i++)
    {
        scanf("%d %d %d", &temp1, &temp2, &temp3);
        temp1--;
        temp2--;
        if(dist[temp1][temp2] == -1 || dist[temp1][temp2] > temp3)
            dist[temp1][temp2] = temp3;
        if(dist[temp2][temp1] == -1 || dist[temp2][temp1] > temp3)
            dist[temp2][temp1] = temp3;
    }
    for(int inter = 0; inter < nodes; inter++)
    {
        for(int start = 0; start < nodes; start++)
        {
            for(int end = 0; end < nodes; end++)
            {
                if(dist[start][inter] != -1 && dist[inter][end] != -1)
                {
                    if(dist[start][end] == -1 || dist[start][end] > dist[start][inter] + dist[inter][end])
                        dist[start][end] = dist[start][inter] + dist[inter][end];
                }
            }
        }
    }
    int start, end;
    while(amountq--)
    {
        scanf("%d %d", &start, &end);
        start--;
        end--;
        printf("%lld\n", dist[start][end]);
    }
}