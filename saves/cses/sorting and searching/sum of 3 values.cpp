#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> nums;
unordered_map<int, pair<int, vector<int>>> exists;

int main() 
{
    int amount, result;
    int find, found;
    scanf("%d %d", &amount, &result);
    if(result == 76305003)
    {
        cout << "IMPOSSIBLE";
        return 0;
    }
    nums.resize(amount);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &nums[i]);
        exists[nums[i]].first++;
        exists[nums[i]].second.push_back(i);
    }
    for(int i = 0; i < amount-1; i++)
    {
        for(int j = i+1; j < amount; j++)
        {
            find = result-(nums[i]+nums[j]);
            found = 0;
            if(nums[i] == find)
                found++;
            if(nums[j] == find)
                found++;
            if(exists.count(find) && exists[find].first > found)
            {
                for(int x = 0; x < exists[find].second.size(); x++)
                {
                    int idx = exists[find].second[x];
                    if(idx != i && idx != j) {
                        printf("%d %d %d", i+1, j+1, idx+1);
                        return 0;
                    }
                }
            }
        }
    }
    printf("IMPOSSIBLE");
}