#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;

vector<int> pos;

int main() 
{
    ll n;
    scanf("%lld", &n);
    printf("%lld ", n);
    while(n > 1)
    {
        if(n % 2 == 0)
        {
            n /= 2;
        }
        else
        {
            n *= 3;
            n++;
        }
        printf("%lld ", n);
    }
}