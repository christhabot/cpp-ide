#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> vec;
vector<ll> pref;

int main() {
    int amount;
    int start, end, sum;
    int goal, res = 0;
    bool cond = true;
    scanf("%d %d", &amount, &goal);
    vec.resize(amount);
    pref.resize(amount);
    scanf("%d", &vec[0]);
    pref[0] = vec[0];
    for(int i = 1; i < amount; i++)
    {
        scanf("%d", &vec[i]);
        pref[i] = pref[i-1] + vec[i];
    }
    start = 0;
    end = 0;
    while(cond)
    {
        if(start == 0)
            sum = pref[end];
        else
            sum = pref[end] - pref[start-1];
        if(sum == goal)
        {
            res++;
            start++;
        }
        else
        {
            if(sum < goal)
            {
                if(end >= amount-1)
                {
                    cond = false;
                }
                end++;
            }
            else
            {
                start++;
                end = max(start, end);
                if(start == amount)
                {
                    cond = false;
                }
            }
        }
    }
    printf("%d", res);
}