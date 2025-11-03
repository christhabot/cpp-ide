#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<pair<int,int>> vec;
// value, idx

int main() 
{
    int amount, target, temp;
    scanf("%d %d", &amount, &target);
    vec.resize(amount);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &temp);
        vec[i] = {temp, i};
    }
    sort(vec.begin(), vec.end());
    int l = 0, r = amount-1, cur;
    while(l < r)
    {
        cur = vec[l].first + vec[r].first;
        if(cur == target)
        {
            printf("%d %d", vec[l].second+1, vec[r].second+1);
            return 0;
        }
        else if(cur < target)
        {
            l++;
        }
        else
        {
            r--;
        }
    }
    printf("IMPOSSIBLE");
}