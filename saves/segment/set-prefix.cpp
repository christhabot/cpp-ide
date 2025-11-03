#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> seg;
int amount;

void build()
{
    for(int i = amount-1; i > 0; i--)
    {
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }
}

void modify(int pos, int val)
{
    pos += amount;
    for(seg[pos] = val; pos > 1; pos >>= 1)
    {
        seg[pos >> 1] = seg[pos] + seg[pos ^ 1];
    }
}

ll pref(int pos) {
    ll res = 0;
    int l = amount;
    int r = pos + amount + 1;
    while (l < r) {
        if (l & 1) res += seg[l++];
        if (r & 1) res += seg[--r];
        l >>= 1; r >>= 1;
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
            if(b > 0)
                printf("%lld\n", pref(c) - pref(b-1));
            else
                printf("%lld\n", pref(c));
        }
    }
}