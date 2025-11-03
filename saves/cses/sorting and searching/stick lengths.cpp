#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> vec;

ll check(int val)
{
    ll total = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        total += abs(vec[i] - val);
    }
    return total;
}

int main() 
{
    int amount, av;
    scanf("%d", &amount);
    vec.resize(amount);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &vec[i]);
    }
    sort(vec.begin(), vec.end());
    av = vec[amount/2];
    printf("%lld", check(av));
}