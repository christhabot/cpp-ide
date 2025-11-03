#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int>> moves;
queue<pair<int,int>> st;
vector<pair<int,int>> kmoves = {
    { 2,  1},
    { 2, -1},
    {-2,  1},
    {-2, -1},
    { 1,  2},
    { 1, -2},
    {-1,  2},
    {-1, -2}
};

int main() 
{
    int n, newx, newy;
    pair<int,int> tp;
    scanf("%d", &n);
    moves.assign(n, vector<int>(n,-1));
    moves[0][0] = 0;
    st.push({0,0});
    while(!st.empty())
    {
        tp = st.front();
        st.pop();
        for(auto&& move : kmoves)
        {
            newx = tp.first + move.first;
            newy = tp.second + move.second;
            if(!(newx < 0 || newx >= n || newy < 0 || newy >= n) && moves[newy][newx] == -1)
            {
                moves[newy][newx] = moves[tp.second][tp.first] + 1;
                st.push({newx, newy});
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d ", moves[i][j]);
        }
        printf("\n");
    }
}