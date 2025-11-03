#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    vector<bool> vec;
    ll amount;
    ll temp;
    cin >> amount;
    vec.assign(amount+1,false);
    for(ll i = 0; i < amount; i++)
    {
        cin >> temp;
        vec[temp] = true;
    }
    for(ll i = 1; i <= amount; i++)
    {
        if(!vec[i]) cout << i;
    }
}