#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) return 0;
    ll last = n % 10;
    ll other = n - last;
    vector<ll> out;

    for (ll i = 1; i * i <= other; ++i) {
        if (other % i == 0) {
            ll d1 = i;
            ll d2 = other / i;
            if (d1 > last && d1 <= n) out.push_back(d1);
            if (d2 > last && d2 <= n && d2 != d1) out.push_back(d2);
        }
    }

    sort(out.begin(), out.end());
    out.erase(unique(out.begin(), out.end()), out.end());

    printf("%lld\n", (ll)out.size());
    for (ll x : out) printf("%lld ", x);
    printf("\n");
    return 0;
}
