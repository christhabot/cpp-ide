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
    bef = pos[1];
    for(int i = 2; i <= amount; i++)
    {
        cur = pos[i];
        if(cur < bef)
        {
            total++;
        }
        bef = cur;
    }
    printf("%d", total);
}