#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool overlaps(ll l1, ll r1, ll l2, ll r2) {
    return max(l1, l2) <= min(r1, r2);
}

int main() {
    ll amount, amountq;
    scanf("%lld", &amount);

    vector<pair<ll,ll>> sofar(amount);
    for (int i = 0; i < amount; i++) {
        scanf("%lld %lld", &sofar[i].first, &sofar[i].second);
    }

    vector<ll> nextBreak(amount);
    set<pair<ll,ll>> st;
    ll r = 0;
    for (ll l = 0; l < amount; l++) {
        while (r < amount) {
            auto [L, R] = sofar[r];
            auto it = st.lower_bound({L, LLONG_MIN});
            bool bad = false;
            if (it != st.end() && overlaps(it->first, it->second, L, R)) bad = true;
            if (it != st.begin()) {
                auto pit = prev(it);
                if (overlaps(pit->first, pit->second, L, R)) bad = true;
            }
            if (bad) break;
            st.emplace(L, R);
            r++;
        }
        nextBreak[l] = r;
        st.erase(sofar[l]);
    }

    const int LOG = 18; // <= 2e5
    vector<vector<ll>> up(LOG, vector<ll>(amount+1, amount));
    for (int i = 0; i < amount; i++) {
        up[0][i] = nextBreak[i];
    }
    up[0][amount] = amount;
    for (int k = 1; k < LOG; k++) {
        for (int i = 0; i <= amount; i++) {
            up[k][i] = up[k-1][ up[k-1][i] ];
        }
    }

    scanf("%lld", &amountq);
    while (amountq--) {
        ll p, q;
        scanf("%lld %lld", &p, &q);
        ll l = p-1, r0 = q-1;

        ll cur = l;
        ll need = r0 + 1;
        ll ans = 0;
        for (int k = LOG-1; k >= 0; k--) {
            if (up[k][cur] < need) {
                cur = up[k][cur];
                ans += (1LL << k);
            }
        }
        ans++;
        printf("%lld\n", ans);
    }

    return 0;
}
