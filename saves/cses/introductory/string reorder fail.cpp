#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<bool> used;
vector<int> soonest;

int main() 
{
    string input, output;
    int small = 0, leastunused = 1, i;
    cin >> input;
    sort(input.begin(), input.end());
    soonest.assign(input.size(), -1);
    soonest.back() = soonest.size()-1;
    for(int i = input.size()-2; i >= 0; i--)
    {
        if(input[i] == input[i+1])
            soonest[i] = soonest[i+1];
        else
            soonest[i] = i;
    }
    used.assign(input.size(), false);
    output.push_back(input[0]);
    used[0] = true;
    while(output.size() < input.size())
    {
        i = leastunused;
        if(input[i] == output.back())
            i = soonest[i] + 1;
        while(used[i])
        {
            i++;
        }
        output.push_back(input[i]);
        used[i] = true;
        if(i <= leastunused)
        {
            while(used[i])
            {
                i++;
            }
            leastunused = i;
        }
    }
    cout << output;
}