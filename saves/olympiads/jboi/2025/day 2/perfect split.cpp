#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll cnt(ll n)
{
    ll out = 0;
    string s = to_string(n);
    for(ll i = 0; i < s.size(); i++)
    {
        out += s[i] - '0';
    }
    return out;
}

int main()
{
    ll num, cntn;
    ll s;
    scanf("%lld", &num);
    cntn = cnt(num);
    for(ll i = 0; i < num; i++)
    {
        s = num - i;
        if(cnt(i) == cntn && cnt(s) == cntn)
        {
            printf("%lld %lld", i, s);
            return 0;
        }
    }
    printf("-1");
    return 0;
}
