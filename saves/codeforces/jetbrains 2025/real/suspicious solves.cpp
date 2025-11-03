#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<char>> teamcnt;
vector<ll> cnt;

int main()
{
    ll teams, problems, solves;
    scanf("%lld %lld %lld", &teams, &problems, &solves);

    teamcnt.assign(teams+1, vector<char>(problems+1, 0));
    cnt.assign(problems+1, 0);

    for(ll i = 0; i < solves; i++)
    {
        ll team, solve;
        scanf("%lld %lld", &team, &solve);

        ll suspicious = 0;
        for(ll prob = 1; prob <= problems; prob++)
        {
            if(!teamcnt[team][prob] && cnt[prob] > cnt[solve])
            {
                suspicious++;
            }
        }

        printf("%lld\n", suspicious);

        teamcnt[team][solve] = 1;
        cnt[solve] += 1;
    }
}
