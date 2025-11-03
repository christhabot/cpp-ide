#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
vector<vector<char>> vec;
queue<pair<int, int>> q;
vector<vector<bool>> visited;
vector<vector<char>> dir;
vector<char> path;

int main() {
    int x, y;
    cin >> x >> y;
    char temp;
    pair<int, int> qf;
    vec.assign(x, vector<char>());
    dir.assign(x+1, vector<char>(y+1, 'e'));
    visited.assign(x,vector<bool>(y, false));
    int sx = -1, sy = -1, ex = -1, ey = -1;
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            cin >> temp;
            if(temp == 'A')
            {
                sx = i;
                sy = j;
                vec[i].push_back('.');
            }
            else if(temp == 'B')
            {
                ex = i;
                ey = j;
                vec[i].push_back('.');
            }
            else
            {
                vec[i].push_back(temp);
            }
        }
    }
    if (sx == -1 || ex == -1) {
        cout << "NOO";
        return 0;
    }

    q.push({sx,sy});
    visited[sx][sy] = true;
    while(!q.empty() && !(q.front().first == ex && q.front().second == ey))
    {
        qf = q.front();
        if(qf.first > 0 && vec[qf.first-1][qf.second] == '.' && !visited[qf.first-1][qf.second])
        {
            visited[qf.first-1][qf.second] = true;
            q.push({qf.first-1, qf.second});
            dir[qf.first-1][qf.second] = 'U';
        }
        if(qf.second > 0 && vec[qf.first][qf.second-1] == '.' && !visited[qf.first][qf.second-1])
        {
            visited[qf.first][qf.second-1] = true;
            q.push({qf.first, qf.second-1});
            dir[qf.first][qf.second-1] = 'L';
        }
        if(qf.first < x-1 && vec[qf.first+1][qf.second] == '.' && !visited[qf.first+1][qf.second])
        {
            visited[qf.first+1][qf.second] = true;
            q.push({qf.first+1, qf.second});
            dir[qf.first+1][qf.second] = 'D';
        }
        if(qf.second < y-1 && vec[qf.first][qf.second+1] == '.' && !visited[qf.first][qf.second+1])
        {
            visited[qf.first][qf.second+1] = true;
            q.push({qf.first, qf.second+1});
            dir[qf.first][qf.second+1] = 'R';
           
        }
        q.pop();
    }
    int idxx, idxy;
    if(!q.empty())
    {
        cout << "YES\n";
        idxx = ex;
        idxy = ey;
        while(idxx != sx || idxy != sy)
        {
            path.push_back(dir[idxx][idxy]);
            if(dir[idxx][idxy] == 'U')
            {
                idxx++;
            }
            else if(dir[idxx][idxy] == 'D')
            {
                idxx--;
            }
            else if(dir[idxx][idxy] == 'L')
            {
                idxy++;
            }
            else if(dir[idxx][idxy] == 'R')
            {
                idxy--;
            }
        }
        cout << path.size() << "\n";
        for(int i = path.size()-1; i >= 0; i--)
        {
            cout << path[i];
        }
    }
    else cout << "NO";
}