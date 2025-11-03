#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll classes, weeks, bigpoints = 0, answer = 0;
vector<ll> points;

bool is_possible(ll pointss)
{
    __int128_t total = 0;
    for(ll i = 0; i < classes; i++)
    {
        total += (pointss + points[i] - 1) / points[i];
    }
    if(total <= (__int128_t)classes*weeks) return true;
    return false;
}

int main() {
    scanf("%lld %lld", &classes, &weeks);
    points.resize(classes);
    for(ll i = 0; i < classes; i++)
    {
        scanf("%lld", &points[i]);
        bigpoints = max(bigpoints, points[i]);
    }
    
    __int128_t l = 0, r = (__int128_t)bigpoints * weeks;
    while (l<r)
    {
        ll mid = (l + r + 1) / 2;
        if(is_possible(mid)) 
        {
            answer = mid;
            l = mid;
        }
        else r = mid - 1;
    }
    printf("%lld\n", answer);
    return 0;
}