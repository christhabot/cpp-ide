#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int>> connections;
vector<bool> explored;
vector<int> color;
bool possible = true;

void dfs(int pos, bool col)
{
    explored[pos] = true;
    color[pos] = col;
    for(int i = 0; i < connections[pos].size() && possible; i++)
    {
        if(color[connections[pos][i]] == col)
        {
            possible = false;
            return;
        }
        if(!explored[connections[pos][i]])
        {
            dfs(connections[pos][i], !col);
        }
    }
}

int main() 
{
    int amount, amountc;
    int temp1, temp2;
    scanf("%d %d", &amount, &amountc);
    explored.assign(amount, false);
    connections.assign(amount, vector<int>());
    color.assign(amount, -1);
    for(int i = 0; i < amountc; i++)
    {
        scanf("%d %d", &temp1, &temp2);
        temp1--;
        temp2--;
        connections[temp1].push_back(temp2);
        connections[temp2].push_back(temp1);
    }
    for(int i = 0; i < amount && possible; i++)
    {
        if(!explored[i])
        {
            dfs(i, false);
        }
    }
    if(possible)
    {
        for(int i = 0; i < amount; i++)
        {
            printf("%d ", color[i]+1);
        }
    }
    else
        printf("IMPOSSIBLE");
}