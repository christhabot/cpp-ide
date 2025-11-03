#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> seg;
int amount;

void build()
{
    for(int i = amount-1; i > 0; i--)
    {
        // pref, min
        // seg[i] = seg[i << 1] + seg[i << 1 | 1];
        seg[i] = min(seg[i << 1], seg[i << 1 | 1]);
    }
}

void modify(int pos, int val)
{
    pos += amount;
    for(seg[pos] = val; pos > 1; pos >>= 1)
    {
        // pref, min
        // seg[pos >> 1] = seg[pos] + seg[pos ^ 1];
        seg[pos >> 1] = min(seg[pos], seg[pos ^ 1]);
    }
}

ll pref(int pos) {
    ll res = 0;
    for (int l = amount; r = pos + amount + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += seg[l++];
        if (r & 1) res += seg[--r];
    }
    return res;
}

ll range_min(int l, int r) {
    ll res = LLONG_MAX;
    for(l += amount, r += amount + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = min(res, seg[l++]);
        if (r & 1) res = min(res, seg[--r]);
    }
    return res;
}


int main() 
{
    int amountq;
    int a, b, c;
    scanf("%d %d", &amount, &amountq);
    seg.resize(amount*2);
    for(int i = 0; i < amount; i++)
    {
        scanf("%lld", &seg[i+amount]);
    }
    build();
    while(amountq--)
    {
        scanf("%d %d %d", &a, &b, &c);
        if(a == 1)
        {
            b--;
            modify(b, c);
        }
        else
        {
            b--;
            c--;
            printf("%lld\n", range_min(b, c));
        }
    }
}