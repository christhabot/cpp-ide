#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int weight;
int amounta, amountb;

vector<int> haya, hayb;
vector<vector<ll>> memo;
vector<ll> prefa, prefb;

ll dp(int a, int b)
{
    if (a >= amounta && b >= amountb) return 0;
    if (memo[a][b] != -1) return memo[a][b];

    ll result = LLONG_MAX;

    for (int next_a = a; next_a <= amounta; next_a++) {
        ll weighta = prefa[next_a] - prefa[a];
        if (weighta > weight) break;
        
        int next_b = b;
        while (next_b + 1 <= amountb && weighta + (prefb[next_b + 1] - prefb[b]) <= weight)
            next_b++;

        if (next_a == a && next_b == b) continue;

        ll next = dp(next_a, next_b);
        if (next != LLONG_MAX)
            result = min(result, next + 1);
    }

    return memo[a][b] = result;
}

int main() 
{
    bool allsame = true, asame = true;
    scanf("%d %d %d", &amounta, &amountb, &weight);
    haya.resize(amounta);
    hayb.resize(amountb);
    memo.assign(amounta + 1, vector<ll>(amountb + 1, -1));
    for(int i = 0; i < amounta; i++)
    {
        scanf("%d", &haya[i]);
        if(i > 0 && haya[i] != haya[i-1])
        {
            allsame = false;
            asame = false;
        }
    }
    for(int i = 0; i < amountb; i++)
    {
        scanf("%d", &hayb[i]);
        if(i > 0 && hayb[i] != hayb[i-1])
        {
            allsame = false;
        }
    }
    prefa.resize(amounta+1);
    prefb.resize(amountb+1);
    for (int i = 0; i < amounta; i++) prefa[i+1] = prefa[i] + haya[i];
    for (int i = 0; i < amountb; i++) prefb[i+1] = prefb[i] + hayb[i];
    if(allsame) // subtask 1
    {
        ll getper = weight / haya[0];
        printf("%lld", (ll)ceil((amounta+amountb)/(getper * 1.0)));
    }
    else if(asame) // subtask 2
    {
        ll total = 0, loadedb = 0, loadeda = 0;
        while(loadedb < amountb)
        {
            ll cur = 0;
            int start = loadedb;
            
            while(loadedb < amountb && cur + hayb[loadedb] <= weight)
            {
                cur += hayb[loadedb];
                loadedb++;
            }
            
            loadeda += weight - cur;
            total++;
        }
        
        if(loadeda < amounta) {
            total += (amounta - loadeda + weight - 1) / weight;
        }
        printf("%lld", total);
    }
    else
    {
        printf("%lld\n", dp(0, 0));
    }
}