#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ll t;
    scanf("%lld", &t);
    while(t--) {
        ll r1, r2, r3;
        scanf("%lld %lld %lld", &r1, &r2, &r3); // time to 1, time to 2, time from 1 to 2
        ll q1, q2, t1;
        scanf("%lld %lld %lld", &q1, &q2, &t1); // open times for 1, time taken for 1
        ll w1, w2, t2;
        scanf("%lld %lld %lld", &w1, &w2, &t2); // open times for 2, time taken for 2
        
        ll arriv1 = min(r1, r2 + r3);
        arriv1 = max(arriv1, q1);
        ll leave1 = arriv1 + t1;
        ll arriv2 = leave1 + min(r3, r1 + r2);
        arriv2 = max(arriv2, w1);
        ll leave2 = arriv2 + t2;
        if(leave1 <= q2 && leave2 <= w2)
        {
            printf("1\n");
        }
        else
        {
            arriv2 = min(r2, r1 + r3);
            arriv2 = max(arriv2, w1);
            leave2 = arriv2 + t2;

            arriv1 = leave2 + min(r3, r2 + r1);
            arriv1 = max(arriv1, q1);
            leave1 = arriv1 + t1;
            if(leave1 <= q2 && leave2 <= w2)
            {
                printf("1\n");
            }
            else
            {
                printf("0\n");
            }
        }
    }
}