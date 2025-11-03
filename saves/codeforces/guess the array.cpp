#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> vec;

int main() 
{
    ll amount;
    ll ab, bc, ac;
    ll temp;
    scanf("%lld", &amount);
    printf("? 1 2\n");
    fflush(stdout);
    scanf("%lld", &ab);
    printf("? 2 3\n");
    fflush(stdout);
    scanf("%lld", &bc);
    printf("? 1 3\n");
    fflush(stdout);
    scanf("%lld", &ac);
    vec.push_back((ab + ac - bc) / 2);
    vec.push_back(ab-vec[0]);
    vec.push_back(bc-vec[1]);
    for(ll i = 3; i < amount; i++)
    {
        printf("? %lld %lld\n", i, i+1);
        fflush(stdout);
        scanf("%lld", &temp);
        vec.push_back(temp-vec[i-1]);
    }
    printf("!");
    for(int i = 0; i < amount; i++)
    {
        printf(" %lld", vec[i]);
    }
    fflush(stdout);
}