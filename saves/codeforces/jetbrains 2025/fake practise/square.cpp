#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() 
{
    ll amountq;
    ll a1, a2, b1, b2;
    bool good;
    scanf("%lld", &amountq);
    while(amountq--)
    {
        scanf("%lld %lld %lld %lld", &a1, &b1, &a2, &b2);
        good = false;
        ll r1[2][2] = {{a1, b1}, {b1, a1}};
        ll r2[2][2] = {{a2, b2}, {b2, a2}};

        for (int i = 0; i < 2 && !good; i++) 
        {
            for (int j = 0; j < 2 && !good; j++) 
            {
                int w1 = r1[i][0], h1 = r1[i][1];
                int w2 = r2[j][0], h2 = r2[j][1];

                if (w1 == w2 && h1 + h2 == w1) {
                    good = true;
                }
            }
        }
        if(good)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
}