#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int type, amount;
int best;

vector<vector<int>> vec;

void dfs(int i, int j, int ci, int cj, int length)
{
    int toi, toj;
    if(vec[i][j] == 1)
    {
        if(i < ci) // came from bottom
        {
            toi = i;
            toj = j+1;
        }
        else if(i > ci) // came from top
        {
            toi = i;
            toj = j-1;
        }
        else if(j < cj) // came from right
        {
            toi = i+1;
            toj = j;
        }
        else // came from left
        {
            toi = i-1;
            toj = j;
        }
    }
    else if(vec[i][j] == 2)
    {
        if(i < ci) // came from bottom
        {
            toi = i;
            toj = j-1;
        }
        else if(i > ci) // came from top
        {
            toi = i;
            toj = j+1;
        }
        else if(j < cj) // came from right
        {
            toi = i-1;
            toj = j;
        }
        else // came from left
        {
            toi = i+1;
            toj = j;
        }
    }
    else
    {
        if(i < ci) // came from bottom
        {
            toj = j;
            toi = i-1;
        }
        else if(i > ci) // came from top
        {
            toj = j;
            toi = i+1;
        }
        else if(j < cj) // came from right
        {
            toi = i;
            toj = j-1;
        }
        else // came from left
        {
            toi = i;
            toj = j+1;
        }
    }
    if(toi >= amount || toi < 0 || toj >= amount || toj < 0)
    {
        best = max(best, length);
    }
    else
    {
        dfs(toi, toj, i, j, length+1);
    }
}

int findfastest()
{
    best = 0;
    for(int i = 0; i < amount; i++) // top wall
    {
        dfs(0, i, -1, i, 1);
    }
    for(int i = 0; i < amount; i++) // bottom wall
    {
        dfs(amount-1, i, amount, i, 1);
    }
    for(int i = 0; i < amount; i++) // left wall
    {
        dfs(i, 0, i, -1, 1);
    }
    for(int i = 0; i < amount; i++) // right wall
    {
        dfs(i, amount-1, i, amount, 1);
    }
    return best;
}

int main() 
{
    char temp;
    scanf("%d %d", &type, &amount);
    vec.assign(amount, vector<int>(amount, -1));
    for(int i = 0; i < amount; i++)
    {
        for(int j = 0; j < amount; j++)
        {
            scanf(" %c", &temp);
            vec[i][j] = temp - '0';
        }
    }
    if(type == 1)
    {
        ll v = 0, cross = 0;
        for(int i = 0; i < amount-1; i++)
        {
            for(int j = 0; j < amount-1; j++)
            {
                if(vec[i][j] == 1)
                {
                    if(vec[i][j+1] == 2 && vec[i+1][j] == 2 && vec[i+1][j+1] == 1)
                    {
                        cross++;
                    }
                }
            }
        }
        for(int i = 0; i < amount-1; i++) // top wall
        {
            if(vec[0][i] == 2 && vec[0][i+1] == 1)
                v++;
        }
        for(int i = 0; i < amount-1; i++) // bottom wall
        {
            if(vec[amount-1][i] == 1 && vec[amount-1][i+1] == 2)
                v++;
        }
        for(int i = 0; i < amount-1; i++) // left wall
        {
            if(vec[i][0] == 2 && vec[i+1][0] == 1)
                v++;
        }
        for(int i = 0; i < amount-1; i++) // right wall
        {
            if(vec[i][amount-1] == 1 && vec[i+1][amount-1] == 2)
                v++;
        }
        printf("%lld %lld", v, cross);
    }
    else if(type == 2)
    {
        printf("%d", findfastest());
    }
    else if(type == 3)
    {
        int best2 = 0, ways = 0, old, cur;
        for(int i = 0; i < amount; i++)
        {
            for(int j = 0; j < amount; j++)
            {
                for(int k = 1; k <= 3; k++)
                {
                    if(vec[i][j] == k)
                    {
                        continue;
                    }
                    old = vec[i][j];
                    vec[i][j] = k;
                    cur = findfastest();
                    if(cur > best2)
                    {
                        ways = 1;
                        best2 = cur;
                    }
                    else if(cur == best2)
                    {
                        ways++;
                    }
                    vec[i][j] = old;
                }
            }
        }
        printf("%d %d", best2, ways);
    }
}