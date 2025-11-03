#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> heights;
vector<vector<ll>> connections;
vector<ll> obstacles;

int main() {
    ll amount, temp, temp2, score = 0, cat_start;
    bool gone;
    scanf("%lld", &amount);
    heights.resize(amount);
    obstacles.resize(amount);
    connections.assign(amount, vector<ll>());
    for(int i = 0; i < amount; i++)
    {
        obstacles[i] = i;
        scanf("%lld", &heights[i]);
        if(heights[i] == amount) cat_start = i;
    }
    for(int i = 0; i < amount-1; i++)
    {
        scanf("%lld %lld", &temp, &temp2);
        temp--;
        temp2--;
        connections[temp].push_back(temp2);
        connections[temp2].push_back(temp);
    }
    do
    {
        vector<bool> blocked(amount, false);
        int cat_pos = cat_start;
        ll moves = 0;

        for (int tower : obstacles)
        {
            if (blocked[tower]) continue;
            
            blocked[tower] = true;

            if (tower == cat_pos)
            {
                bool all_blocked = true;
                for (int adj : connections[cat_pos])
                {
                    if (!blocked[adj])
                    {
                        all_blocked = false;
                        break;
                    }
                }
                if (all_blocked)
                    break;  // cant move
                
                // bfs
                vector<int> dist(amount, -1);
                queue<int> q;
                dist[cat_pos] = 0;
                q.push(cat_pos);
                while (!q.empty())
                {
                    int u = q.front(); q.pop();
                    for (int v : connections[u])
                    {
                        if (!blocked[v] && dist[v] == -1)
                        {
                            dist[v] = dist[u] + 1;
                            q.push(v);
                        }
                    }
                }

                // find highest reachable tower
                int next_tower = -1;
                int max_height = -1;
                int min_dist = INT_MAX;
                for (int i = 0; i < amount; i++)
                {
                    if (i != cat_pos && dist[i] != -1)
                    {
                        if (heights[i] > max_height || (heights[i] == max_height && dist[i] < min_dist))
                        {
                            max_height = heights[i];
                            min_dist = dist[i];
                            next_tower = i;
                        }
                    }
                }

                if (next_tower == -1) break;  // cant move

                moves += dist[next_tower];
                cat_pos = next_tower;
            }
        }
        score = max(score, moves);
    } while (next_permutation(obstacles.begin(), obstacles.end()));
    cout << score << "\n";
}