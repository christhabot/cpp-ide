#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<ll>> connections;

ll n, m, temp, temp2;

vector<bool> explored;
vector<int> parent;
queue<int> q;
stack<int> s;

int main() {
    ll current, size = 0;
    cin >> n >> m;
    bool found = false;
    explored.assign(n+1, false);
    connections.resize(n + 1);
    parent.resize(n+1);
    for(int i = 0; i < m; i++)
    {
        cin >> temp >> temp2;
        connections[temp].push_back(temp2);
        connections[temp2].push_back(temp);
    }
    q.push(1);
    while(!found && !q.empty())
    {
        if(q.front() == n)
        {
            found = true;
            continue;
        }
        for(int i = 0; i < connections[q.front()].size(); i++)
        {
            if(!explored[connections[q.front()][i]]) 
            {
                explored[connections[q.front()][i]] = true;
                q.push(connections[q.front()][i]);
                parent[connections[q.front()][i]] = q.front();
            }
        }
        q.pop();
    }
    if(!found) cout << "IMPOSSIBLE";
    else
    {
        current = n;
        while(current != 1)
        {
            size++;
            s.push(parent[current]);
            current = parent[current];
        }
        cout << size+1 << "\n";
        for(int i = 0; i < size; i++)
        {
            cout << s.top() << " ";
            s.pop();
        }
        cout << q.front();
    }
}