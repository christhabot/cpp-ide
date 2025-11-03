#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> vec;
vector<int> pref;

int main() 
{
    int amount, target;
    int found = 0;
    bool go = true;
    scanf("%d %d", &amount, &target);
    vec.resize(amount);
    pref.resize(amount);
    scanf("%d", &vec[0]);
    pref[0] = vec[0];
    for(int i = 1; i < amount; i++)
    {
        scanf("%d", &vec[i]);
        pref[i] = pref[i-1] + vec[i];
    }
    int l = 0, r = 0;
    while(go)
    {
        if ((l == 0 && pref[r] == target) || (l > 0 && pref[r] - pref[l-1] == target))
        {
            found++;
            r++;
            l++;
        }
        else if ((l == 0 && pref[r] > target) || (l > 0 && pref[r] - pref[l-1] > target))
        {
            l++;
            r = max(r, l);
        }
        else
        {
            r++;
        }
        if(r >= amount)
        {
            l++;
            if(l >= amount)
            {
                go = false;
            }
        }
        if(l >= amount)
        {
            r++;
            if(r >= amount)
            {
                go = false;
            }
        }
    }
    printf("%d", found);
}