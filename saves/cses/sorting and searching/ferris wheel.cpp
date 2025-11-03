#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> weights;

int main() {
    int amount, maxweight;
    int small = -1;
    ll cur;
    int total = 0;
    scanf("%d %d", &amount, &maxweight);
    weights.resize(amount);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &weights[i]);
    }
    sort(weights.begin(), weights.end());
    for(int i = amount-1; i > small; i--)
    {
        total++;
        cur = weights[i];
        if(cur + weights[small+1] <= maxweight)
        {
            cur += weights[small+1];
            small++;
        }
    }
    printf("%d", total);
}