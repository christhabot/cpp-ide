#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() 
{
    ll amountq;
    ll temp1, temp2;
    scanf("%lld", &amountq);
    while(amountq--)
    {
        scanf("%lld %lld", &temp1, &temp2);
        printf("%lld\n", temp1 + temp2);
    }
}