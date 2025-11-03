#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int>> vec;
vector<ll> freq(100001, 0);

int main() 
{
    int amount, amountop;
    char op;
    int from, to, val;
    ll big = 0, small = LLONG_MAX;
    scanf("%d %d", &amount, &amountop);
    vec.assign(amount, vector<int>(amount, -1));
    for(int i = 0; i < amountop; i++)
    {
        scanf(" %c %d %d %d", &op, &from, &to, &val);
        from--;
        to--;
        if(op == 'H')
        {
            for(int j = from; j <= to; j++)
            {
                for(int k = 0; k < amount; k++)
                {
                    vec[j][k] = val;
                }
            }
        }
        else
        {
            for(int j = from; j <= to; j++)
            {
                for(int k = 0; k < amount; k++)
                {
                    vec[k][j] = val;
                }
            }
        }
    }
    for(int i = 0; i < amount; i++)
    {
        for(int j = 0; j < amount; j++)
        {
            if(vec[i][j] != -1)
                freq[vec[i][j]]++;
        }
    }
    for(int i = 0; i < freq.size(); i++)
    {
        big = max(big, freq[i]);
        if(freq[i] > 0)
            small = min(small, freq[i]);
    }
    printf("%lld %lld", small, big);
}