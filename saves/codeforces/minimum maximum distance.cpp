#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> connections;
vector<bool> marked;
vector<bool> keep_node;

bool dfso(int i, int p)
{
    bool ret = marked[i];
    
    for(int neighbor : connections[i])
    {
        if(neighbor != p)
        {
            if(dfso(neighbor, i))
                ret = true;
        }
    }
    
    keep_node[i] = ret;
    return ret;
}

int bfs_farthest(int start, int n)
{
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    int last = start;
    
    while(!q.empty())
    {
        int tp = q.front();
        q.pop();
        last = tp;
        
        for(int neighbor : connections[tp])
        {
            if(keep_node[neighbor] && !visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    return last;
}

int dist(int i, int p, int targ)
{
    if(i == targ)
        return 0;
    
    for(int neighbor : connections[i])
    {
        if(neighbor != p && keep_node[neighbor])
        {
            int d = dist(neighbor, i, targ);
            if(d >= 0)
                return d + 1;
        }
    }
    return -1;
}

int find_root(int n)
{
    for(int i = 0; i < n; i++)
    {
        if(keep_node[i])
        {
            int kept_neighbors = 0;
            for(int neighbor : connections[i])
            {
                if(keep_node[neighbor])
                    kept_neighbors++;
            }
            if(kept_neighbors >= 2 || marked[i])
                return i;
        }
    }
    for(int i = 0; i < n; i++)
    {
        if(keep_node[i])
            return i;
    }
    return 0;
}

int main() 
{
    int amountq, amount, amountm, temp, temp2;
    scanf("%d", &amountq);
    while(amountq--)
    {
        scanf("%d %d", &amount, &amountm);
        marked.assign(amount, false);
        keep_node.assign(amount, false);
        
        int first_marked = -1;
        for(int i = 0; i < amountm; i++)
        {
            scanf("%d", &temp);
            temp--;
            marked[temp] = true;
            if(first_marked == -1)
                first_marked = temp;
        }
        
        connections.assign(amount, vector<int>());
        for(int i = 0; i < amount-1; i++)
        {
            scanf("%d %d", &temp, &temp2);
            temp--;
            temp2--;
            connections[temp].push_back(temp2);
            connections[temp2].push_back(temp);
        }
        
        dfso(first_marked, -1);
        
        int start = find_root(amount);
        
        int fir = bfs_farthest(start, amount);
        int las = bfs_farthest(fir, amount);
        
        printf("%d\n", (dist(fir, -1, las) + 1) / 2);
    }
}