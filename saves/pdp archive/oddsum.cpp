#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> vec;

int main() 
{
    freopen("oddsum.in", "r", stdin);
    freopen("oddsum.out", "w", stdout);
    int amount, amountq;
    int last, lastneg;
    ll total;
    scanf("%d", &amountq);
    while(amountq--)
    {
        total = 0;
        scanf("%d", &amount);
        vec.resize(amount);
        lastneg = INT_MIN;
        last = -1;
        for(int i = 0; i < amount; i++)
        {
            scanf("%d", &vec[i]);
            if(vec[i] < 0 && abs(vec[i] % 2) == 1)
            {
                lastneg = max(lastneg, vec[i]);
            }
        }
        sort(vec.begin(), vec.end(), greater<int>());
        for(int i = 0; i < amount; i++)
        {
            if(vec[i] <= 0)
                break;
            if(vec[i] % 2 == 1)
                last = i;
            total += vec[i];
        }
        if(total % 2 == 0)
        {
            if(lastneg == INT_MIN && last == -1)
            {
                printf("IMPOSSIBLE\n");
            }
            else if(last == -1)
            {
                total -= abs(lastneg);
                printf("%d\n", total);
            }
            else
            {
                total -= abs(max(abs(vec[last]), abs(lastneg)));
                printf("%d\n", total);
            }
        }
        else
        {
            printf("%d\n", total);
        }
    }
}