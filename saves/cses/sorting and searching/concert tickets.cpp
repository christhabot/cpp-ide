#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

multiset<int> prices;

int main() 
{
    int amount, amountc, willing, temp;
    scanf("%d %d", &amount, &amountc);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &temp);
        prices.insert(temp);
    }
    while(amountc--)
    {
        scanf("%d", &willing);
        auto it = prices.upper_bound(willing);
        if(it != prices.begin())
        {
            --it;
            printf("%d\n", *it);
            prices.erase(it);
        }
        else
        {
            printf("-1\n");
        }
    }
}