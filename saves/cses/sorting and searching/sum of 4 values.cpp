#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> vec;
vector<int> vec2;
unordered_multimap<int, pair<int,int>> vec2m;

int main() 
{
    int amount, target, i1, i2, j1, j2;
    pair<int,int> t1, t2;
    scanf("%d %d", &amount, &target);
    vec.resize(amount);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &vec[i]);
    }
    for(int i = 0; i < amount-1; i++)
    {
        for(int j = i+1; j < amount; j++)
        {
            vec2.push_back(vec[i] + vec[j]);
            vec2m.insert({vec[i] + vec[j], {i, j}});
        }
    }
    for(int i = 0; i < vec2.size(); i++)
    {
        int needed = target - vec2[i];
        auto range = vec2m.equal_range(needed);
        for(auto it = range.first; it != range.second; ++it)
        {
            t1 = vec2m.equal_range(vec2[i]).first->second;
            t2 = it->second;

            int i1 = t1.first+1;
            int i2 = t1.second+1;
            int j1 = t2.first+1;
            int j2 = t2.second+1;

            if(i1 != i2 && i1 != j1 && i1 != j2 && i2 != j1 && i2 != j2 && j1 != j2)
            {
                printf("%d %d %d %d\n", i1, i2, j1, j2);
                return 0;
            }
        }
    }
    printf("IMPOSSIBLE");
}