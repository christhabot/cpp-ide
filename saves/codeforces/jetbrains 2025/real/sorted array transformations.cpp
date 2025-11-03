#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> r, b;
vector<pair<ll,ll>> need;
vector<tuple<ll,ll,ll>> ops;

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    r.resize(n+1);
    b.resize(n+1);

    for (ll i = 1; i <= n; ++i) 
        cin >> r[i];
    for (ll i = 1; i <= n; ++i) 
        cin >> b[i];

    for (ll j = 1; j <= n; ++j) 
    {
        if (r[j] < b[j]) 
        {
            need.emplace_back(j, b[j] - r[j]);
        } 
        else if (r[j] > b[j]) 
        {
            ll give = r[j] - b[j];
            while (give > 0) 
            {
                if (need.empty()) 
                {
                    cout << -1 << '\n';
                    return 0;
                }
                auto &pr = need.back();
                ll i = pr.first;
                ll want = pr.second;
                ll x = min(give, want);
                ops.emplace_back(i, j, x);
                give -= x;
                pr.second -= x;
                if (pr.second == 0) need.pop_back();
            }
        }
    }

    cout << ops.size() << '\n';
    for (auto &t : ops) 
    {
        ll i, j; ll x;
        tie(i, j, x) = t;
        cout << i << ' ' << j << ' ' << x << '\n';
    }
    return 0;
}
