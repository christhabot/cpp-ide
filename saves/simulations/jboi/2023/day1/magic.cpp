#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<pair<pair<ll,ll>,ll>> wizs;
// pos, skill
vector<pair<ll,ll>> good;
// best, pos
vector<ll> goodf;
vector<vector<ll>> vecs;
// 1-50: list: pos

bool big(ll a, ll b, ll c, ll d)
{
    if(b == -1)
        return false;
    return a*d > b*c;
}

int main() 
{
    ll amount;
    ll temp1, temp2;
    bool allsame = true;
    ll last;
    ll fina, finb, xi, dist, div, biggest = -1, besta, bestb;
    scanf("%lld", &amount);
    wizs.resize(amount);
    good.resize(amount);
    goodf.resize(amount);
    for(ll i = 0; i < amount; i++)
    {
        scanf("%lld %lld", &temp1, &temp2);
        wizs[i] = {{temp1, temp2},i};
        if(i > 0 && wizs[i].first.second != wizs[i-1].first.second)
        {
            allsame = false;
        }
        last = temp2;
        biggest = max(biggest, temp2);
    }
    if(allsame) // subtask 1
    {
        sort(wizs.begin(), wizs.end());
        for(ll i = 0; i < amount; i++)
        {
            good[i].second = wizs[i].second;
            if(i > 0 && i < amount-1)
            {
                xi = wizs[i].first.first;
                ll d1 = abs(xi - wizs[i-1].first.first);
                ll d2 = abs(wizs[i+1].first.first - xi);
                dist = min(d1, d2);
                good[i].first = dist;
            }
            else if(i > 0)
            {
                good[i].first = abs(wizs[i].first.first - wizs[i-1].first.first);
            }
            else
            {
                good[i].first = abs(wizs[i].first.first - wizs[i+1].first.first);
            }
        }
        for(ll i = 0; i < amount; i++)
        {
            goodf[good[i].second] = good[i].first;
        }
        for(ll i = 0; i < amount; i++)
        {
            fina = last / gcd(last, goodf[i]);
            finb = goodf[i] / gcd(last, goodf[i]);
            printf("%lld %lld\n", fina, finb);
        }
    }
    else if (biggest <= 50) // subtask 2
    {
        vector<vector<pair<ll,int>>> vecs(51);
        for (int i = 0; i < amount; ++i) {
            int sk = (int)wizs[i].first.second;
            vecs[sk].push_back({ wizs[i].first.first, i });
        }

        for (int j = 1; j <= 50; ++j) {
            if (!vecs[j].empty()) {
                sort(vecs[j].begin(), vecs[j].end(),
                    [](const pair<ll,int>& a, const pair<ll,int>& b){ return a.first < b.first; });
            }
        }

        for (int i = 0; i < amount; ++i)
        {
            ll besta = 0, bestb = 1;
            ll pos = wizs[i].first.first;

            for (int j = 1; j <= 50; ++j)
            {
                auto &v = vecs[j];
                if (v.empty()) continue;

                int n = (int)v.size();
                auto it = lower_bound(v.begin(), v.end(), pos,
                                    [](const pair<ll,int>& a, const ll &b){ return a.first < b; });
                int right = (int)(it - v.begin());
                int left = right - 1;

                // Skip invalid candidates
                while (right < n && v[right].second == i) ++right;
                while (left >= 0 && v[left].second == i) --left;

                if (left < 0 && right >= n) continue;

                ll local_best = -1;
                if (right < n && left < 0) {
                    local_best = llabs(pos - v[right].first);
                } else if (left >= 0 && right >= n) {
                    local_best = llabs(pos - v[left].first);
                } else {
                    ll leftDist = llabs(pos - v[left].first);
                    ll rightDist = llabs(pos - v[right].first);
                    local_best = min(leftDist, rightDist);
                }

                if (local_best == -1) continue;

                if (!big(besta, bestb, j, local_best)) {
                    besta = j;
                    bestb = local_best;
                }
            }

            ll div = gcd(besta, bestb);
            printf("%lld %lld\n", besta/div, bestb/div);
        }
    }
    else //brute
    {
        ll besta = 0, bestb = -1;
        for(ll i = 0; i < amount; i++)
        {
            besta = 0; bestb = 1;
            for(ll j = 0; j < amount; j++)
            {
                if(j == i)
                {
                    continue;
                }
                if(!big(besta, bestb, wizs[j].first.second, abs(wizs[i].first.first - wizs[j].first.first)))
                {
                    besta = wizs[j].first.second;
                    bestb = abs(wizs[i].first.first - wizs[j].first.first);
                }
                
            }
            div = gcd(besta, bestb);
            printf("%lld %lld\n", besta/div, bestb/div);
        }
    }
}