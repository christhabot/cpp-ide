#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> vec;
vector<ll> memo;

ll amount, outcome, temp;

ll dp(int sum)
{
    ll output;
    bool found = false;
    if(sum == outcome) return 0;
    if(sum > outcome) return -1;
    if(memo[sum] != -2) return memo[sum];
    ll small = LLONG_MAX;
    for(int i = 0; i < amount; i++)
    {
        output = dp(sum+vec[i]);
        if(output != -1) 
        {
            output++;
            small = min(small, output);
        }
    }
    if(small != LLONG_MAX) return memo[sum] = small;
    else return memo[sum] = -1;
}

int main() {
    cin >> amount >> outcome;
    memo.assign(outcome+1,-2);
    for(int i = 0; i < amount; i++)
    {
        cin >> temp;
        vec.push_back(temp);
    }
    ll output2 = dp(0);
    cout << output2;
}