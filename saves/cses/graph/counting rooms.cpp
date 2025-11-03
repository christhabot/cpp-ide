#include <bits/stdc++.h>

using namespace std;

const int maxN = 10000;
int amount = 0;
int height, width, sx, sy;

char arr[maxN][maxN];
bool visited[maxN][maxN];

void dfs(int x, int y)
{
    visited[x][y] = true;
    if(arr[x+1][y] == '.' && !visited[x+1][y] && x+1<height) dfs(x+1,y);
    if(arr[x-1][y] == '.' && !visited[x-1][y] && x-1>=0) dfs(x-1,y);
    if(arr[x][y+1] == '.' && !visited[x][y+1] && y+1<width) dfs(x,y+1);
    if(arr[x][y-1] == '.' && !visited[x][y-1] && y-1>=0) dfs(x,y-1);
}

int main() {
    scanf("%d %d", &height, &width);
    scanf("%d %d", &sx, &sy);
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            scanf(" %c",&arr[i][j]);
        }
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(!visited[i][j] && arr[i][j] == '.')
            {   
                amount++;
                dfs(i,j);
            }
        }
    }
    printf("%d", amount);
}
