#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<ll>> tree;
vector<ll> results;

ll dfs(ll i)
{
    ll result = 0;
    for(int j = 0; j < tree[i].size(); j++)
    {
        result += dfs(tree[i][j]);
    }
    results[i] = result;
    return result + 1;
}

int main() {
    ll amount, temp;
    cin >> amount;
    tree.resize(amount+1);
    results.assign(amount+1,0);
    for(int i = 2; i <= amount; i++)
    {
        cin >> temp;
        tree[temp].push_back(i);
    }
    results[1] = dfs(1) - 1;
    for(int i = 1; i <= amount; i++)
    {
        cout << results[i] << ' ';
    }
}