#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
vector<vector<char>> vec;
queue<pair<pair<int, int>, vector<char>>> q;
vector<vector<bool>> visited;
 
int main() {
    int x, y;
    cin >> x >> y;
    int sx, sy, ex, ey;
    char temp;
    pair<pair<int, int>, vector<char>> qf;
    vec.assign(x,vector<char>());
    visited.assign(x,vector<bool>(y, false));
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
    q.push({{sx,sy},vector<char>()});
    while(!q.empty() && !(q.front().first.first == ex && q.front().first.second == ey))
    {
        qf = q.front();
        if(qf.first.first > 0 && vec[qf.first.first-1][qf.first.second] == '.' && !visited[qf.first.first-1][qf.first.second])
        {
            visited[qf.first.first-1][qf.first.second] = true;
            qf.second.push_back('U');
            q.push({{qf.first.first-1, qf.first.second}, qf.second});
            qf.second.pop_back();
        }
        if(qf.first.second > 0 && vec[qf.first.first][qf.first.second-1] == '.' && !visited[qf.first.first][qf.first.second-1])
        {
            visited[qf.first.first][qf.first.second-1] = true;
            qf.second.push_back('L');
            q.push({{qf.first.first, qf.first.second-1}, qf.second});
            qf.second.pop_back();
        }
        if(qf.first.first < x-1 && vec[qf.first.first+1][qf.first.second] == '.' && !visited[qf.first.first+1][qf.first.second])
        {
            visited[qf.first.first+1][qf.first.second] = true;
            qf.second.push_back('D');
            q.push({{qf.first.first+1, qf.first.second}, qf.second});
            qf.second.pop_back();
        }
        if(qf.first.second < y-1 && vec[qf.first.first][qf.first.second+1] == '.' && !visited[qf.first.first][qf.first.second+1])
        {
            visited[qf.first.first][qf.first.second+1]  = true;
            qf.second.push_back('R');
            q.push({{qf.first.first, qf.first.second+1}, qf.second});
            qf.second.pop_back();
        }
        q.pop();
    }
    if(!q.empty())
    {
        cout << "YES\n";
        cout << q.front().second.size() << "\n";
        for(int i = 0; i < q.front().second.size(); i++)
        {
            cout << q.front().second[i];
        }
    }
    else cout << "NO";
}