#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<pair<ll,ll>> vec;
vector<ll> er;

int main() 
{
    ll amount;
    ll type, a, b, x;
    ll l, r;
    ll count = 0;
    scanf("%lld", &amount);
    for(ll e = 0; e < amount; e++)
    {
        scanf("%lld", &type);
        if(type == 1)
        {
            scanf("%lld %lld", &a, &b);
            vec.push_back({a,b});
        }
        else
        {
            scanf("%lld", &x);
            l = LLONG_MAX;
            r = LLONG_MIN;
            count = 0;
            er.clear();
            for(ll i = 0; i < vec.size(); i++)
            {
                if(vec[i].first <= x && vec[i].second >= x)
                {
                    er.push_back(i);
                    l = min(l, vec[i].first);
                    r = max(r, vec[i].second);
                    count++;
                }
            }
            for (ll i = er.size() - 1; i >= 0; i--)
                vec.erase(vec.begin() + er[i]);
            if(count != 0)
                vec.push_back({l,r});
            printf("%lld\n", count);
        }
    }
}