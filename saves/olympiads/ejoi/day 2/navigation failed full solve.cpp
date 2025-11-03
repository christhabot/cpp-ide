#include <bits/stdc++.h>

using namespace std;

std::pair<int, int> navigate(int currColor, std::vector<int> adjColors)
{
    bool found = false;
    int small = INT_MAX;
    int smalli = -1;
    int smalli2 = -1;
    for(int i = 0; i < adjColors.size(); i++)
    {
        if(adjColors[i] < small)
        {
            small = adjColors[i];
            smalli = i;
        }
    }
    for(int i = adjColors.size(); i >= 0 && !found; i--)
    {
        if(adjColors[i] == small)
        {
            found = true;
            smalli2 = i;
        }
    }
    if(!found)
        return {10/0, 10/0};
    if(small == 2)
        return {-1, -1};
    if(small == 1)
        return {currColor+1, smalli2};
    return {currColor+1, smalli};
}
