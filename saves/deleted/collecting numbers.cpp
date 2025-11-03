#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;

vector<int> pos;

int main() 
{
    int amount, cur, bef, total = 1, temp;
    scanf("%d", &amount);
    pos.resize(amount);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &temp);
        pos[temp] = i;
    }
    bef = pos[0];
    for(int i = 1; i < amount; i++)
    {
        cur = pos[i];
        if(cur < bef)
        {
            total++;
        }
        bef = cur;
    }
    if(total == 1)
    {
        printf("%d", total);
    }
    else
    {
        printf("%d", total+1);
    }
}