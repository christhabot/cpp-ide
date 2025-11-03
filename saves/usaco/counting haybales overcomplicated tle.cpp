#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> pos;
unordered_map<int, int> prefix;

int main() 
{
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);
    int amount, amountq;
    int start, end;
    bool found, found1st1st;
    int val1, val2;
    scanf("%d %d", &amount, &amountq);
    pos.resize(amount);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &pos[i]);
    }
    sort(pos.begin(), pos.end());
    prefix[pos[0]] = 1;
    for(int i = 1; i < amount; i++)
    {
        prefix[pos[i]] = prefix[pos[i-1]] + 1;
    }
    for(int i = 0; i < amountq; i++)
    {
        scanf("%d %d", &start, &end);
        found = false;
        val1 = -1;
        for(int i = start-1; i >= 0 && !found; i--)
        {
            if(prefix.count(i))
            {
                found = true;
                val1 = i;
            }
        }
        found = false;
        val2 = -1;
        for(int i = end; i >= start && !found; i--)
        {
            if(prefix.count(i))
            {
                found = true;
                val2 = i;
            }
        }
        if(val1 == -1 && val2 == -1)
            printf("0\n");
        else if(val1 == -1)
            printf("%d\n", prefix[val2]);
        else if(val2 == -1)
            printf("0\n");
        else
        {
            if(val1 == 0)
                printf("%d\n", prefix[val2]);
            else
                printf("%d\n", prefix[val2]-prefix[val1]);
        }
            
    }
}