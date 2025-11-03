#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


ll powMod(ll x, ll n, ll M) {
    ll res = 1;
    x %= M;
    while(n >= 1) {
        if(n & 1) {
            res = (res * x) % M;
            n--;
        } else {
            x = (x * x) % M;
            n /= 2;
        }
    }
    return res;
}

int main() 
{
    int x; 
    cin >> x;
    printf("%lld", powMod(2,x,1000000007));
    return 0;
}