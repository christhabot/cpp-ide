#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<pair<int,int>> vec;
// finish, start

int main() 
{
    int amount, t1, t2, cur;
    int total = 1, idx = 1;
    scanf("%d", &amount);
    vec.resize(amount);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d %d", &t1, &t2);
        vec[i] = {t2, t1};
    }
    sort(vec.begin(), vec.end());
    cur = vec[0].first;
    while(idx < amount)
    {
        if(vec[idx].second >= cur) {
            total++;
            cur = vec[idx].first;
        }
        idx++;
    }
    printf("%d", total);
}