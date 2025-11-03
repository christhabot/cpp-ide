#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int amount, prev, cur;
    ll total = 0;
    scanf("%d", &amount);
    scanf("%d", &prev);
    for(int i = 1; i < amount; i++)
    {
        scanf("%d", &cur);
        total += max(0, prev - cur);
        cur = max(cur, prev);
        prev = cur;
    }
    printf("%lld", total);
}