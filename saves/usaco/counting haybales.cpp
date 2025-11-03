#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> pos;

int main() 
{
    // freopen("haybales.in", "r", stdin);
    // freopen("haybales.out", "w", stdout);
    int amount, amountq;
    int start, end;
    int l, r;
    scanf("%d %d", &amount, &amountq);
    pos.resize(amount);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &pos[i]);
    }
    sort(pos.begin(), pos.end());
    while(amountq--)
    {
        scanf("%d %d", &start, &end);
        l = lower_bound(pos.begin(), pos.end(), start) - pos.begin();
        r = upper_bound(pos.begin(), pos.end(), end) - pos.begin();
        printf("%d\n", r-l);
    }
}