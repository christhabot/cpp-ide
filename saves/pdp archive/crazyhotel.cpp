#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> vec;

int main()
{
    freopen("crazyhotel.in", "r", stdin);
    freopen("crazyhotel.out", "w", stdout);
    ll amount, total, day, cur;
    ll res = 0;
    bool skip = false;
    scanf("%lld %lld %lld", &amount, &total, &day);
    vec.resize(amount);
    for(ll i = 0; i < amount; i++)
    {
        scanf("%lld", &vec[i]);
    }
    ll l = 0, r = 0;
    cur = vec[0];
    while(l < amount)
    {
        skip = false;
        r = l;
        cur = vec[r];
        while(r+1 < amount && cur + vec[r+1] < total)
        {
            r++;
            cur += vec[r];
            if(vec[r] > day)
            {
                if(cur < total)
                {
                    r--;
                    res += r-l+1;
                }
                skip = true;
                l = r+1;
            }
        }
        if(cur < total && !skip)
        {
            res += r-l+1;
        }
        l++;
    }
    printf("%lld\n", res);
}