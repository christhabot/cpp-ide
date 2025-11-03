#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int number;
vector<vector<bool>> grid;
vector<vector<ll>> memo;

ll dp(int i, int j)
{
    ll total = 0;
    if(i == number-1 && j == number-1) return 1;
    if(memo[i][j] != -1) return memo[i][j];
    if(i+1 < number && !grid[i+1][j])
    {
        total += dp(i+1, j);
    }
    if(j+1 < number && !grid[i][j+1])
    {
        total += dp(i, j+1);
    }
    return memo[i][j] = total % 1000000007;
}

int main() 
{
    char temp;
    scanf("%d", &number);
    memo.assign(number, vector<ll>(number, -1));
    grid.assign(number, vector<bool>(number, false));
    for(int i = 0; i < number; i++)
    {
        for(int j = 0; j < number; j++)
        {
            scanf(" %c", &temp);
            if(temp == '*')
            {
                grid[i][j] = true;
            }
        }
    }
    if(grid[0][0])
        printf("0");
    else
        printf("%lld", dp(0,0)%1000000007);
}