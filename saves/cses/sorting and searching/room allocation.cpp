#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;

int main() {
    ll amount, temp, temp2, total = 0, temp3, room_id;
    vector<ll> answers(200005,-1);
    vector<pair<pair<ll,ll>,ll>> vec;
    priority_queue<
        pair<ll,ll>,
        vector<pair<ll,ll>>,
        greater<pair<ll,ll>>
    > people;
    cin >> amount;
    for(ll i = 0; i < amount; i++)
    {
        cin >> temp >> temp2;
        vec.push_back({{temp,temp2},i});
    }
    sort(vec.begin(),vec.end());
    for(ll i = 0; i < amount; i++)
    {
        temp = vec[i].first.first;
        temp2 = vec[i].first.second;
        temp3 = vec[i].second;
        if(!people.empty() && people.top().first < temp)
        {
            room_id = people.top().second;
            people.pop();
        }
        else
        {
            total++;
            room_id = total;
        }
        people.push({temp2,room_id});
        answers[temp3] = room_id;
    }
    cout << total << "\n";
    for(ll i = 0; i < amount; i++)
    {
        cout << answers[i] << ' ';
    }
    return 0;
}