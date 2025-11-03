#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> pos;
unordered_map<int, int> prefix;

int main() 
{
    int amount, amountq;
    int start, end;
    bool found;
    int val1, val2;
    scanf("%d %d", &amount, &amountq);
    pos.resize(amount);
    prefix.resize(1e9);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &pos[i]);
    }
    sort(pos.begin(), pos.end());
    prefix[pos[0]] = 1;
    last = pos[0];
    for(int i = 1; i < amount; i++)
    {
        prefix[pos[i]] = prefix[pos[i-1]]+1;
    }
    for(int i = 0; i < amountq; i++)
    {
        scanf("%d %d", &start, &end);
        found = false;
        for(int i = start; i >= 0 && !found; i--)
        {
            if(prefix.count(i))
            {
                found == true;
                val1 = i;
            }
        }
        found = false;
        for(int i = end; i >= start && !found; i--)
        {
            if(prefix.count(i))
            {
                found == true;
                val1 = i;
            }
        }
}