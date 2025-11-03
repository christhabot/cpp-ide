#include <bits/stdc++.h>

using namespace std;

std::pair<int, int> navigate(int currColor, std::vector<int> adjColors)
{
    int small = INT_MAX;
    int smalli = -1;
    for(int i = 0; i < adjColors.size(); i++)
    {
        if(adjColors[i] < small)
        {
            small = adjColors[i];
            smalli = i;
        }
    }
    if(adjColors.size() >= 3 && currColor != 2)
    {
        return {2, smalli};
    }
    if(small == 3)
        return {-1, -1};
    if(small == 2 && currColor != 2)
        return {2, smalli};
    return {small + 1, smalli};
}
