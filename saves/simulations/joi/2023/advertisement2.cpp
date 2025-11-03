#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> llp;

vector<pair<ll,ll>> people;
vector<pair<ll,ll>> influencing;

bool isInfluenced(llp j)
{
    for(ll i = 0; i < influencing.size(); i++)
    {
        ll Ei = influencing[i].first;
        ll Xi = influencing[i].second;
        ll Ej = j.first;
        ll Xj = j.second;

        if (Ei >= Ej && abs(Xi - Xj) <= Ei - Ej)
        {
            return true;
        }
    }
    return false;
}

int main() {
    bool allsame = true;
    ll amount, n, p, result = 0;
    ll sn;
    set<ll> s;
    scanf("%lld", &amount);
    people.clear();
    for(ll i = 0; i < amount; i++)
    {
        scanf("%lld %lld", &p, &n);
        if(i == 0) sn = n;
        else if(n != sn)
            allsame = false;
        people.push_back({n, p});
        s.insert(p);
    }
    sort(people.begin(), people.end());

    if(allsame)
    {
        cout << s.size();
        return 0;
    }
    influencing.push_back(people[amount-1]);
    // cout << people[amount-1].second << " " << people[amount-1].first << "e\n";
    result++;
    for(ll i = amount-2; i >= 0; i--)
    {
        if(!isInfluenced(people[i]))
        {
            // cout << people[i].second << " " << people[i].first << "\n";
            influencing.push_back(people[i]);
            result++;
        }
    }
    printf("%lld", result);
}