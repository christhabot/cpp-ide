#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> seg;
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

int pref(int pos) {
    int res = 0;
    for (pos += amount + 1; pos > 0; pos >>= 1) {
        if (pos & 1) res += seg[--pos];
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
        scanf("%d", &seg[i+amount]);
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
                printf("%d\n", pref(c) - pref(b-1));
            else
                printf("%d\n", pref(c));
        }
    }
}