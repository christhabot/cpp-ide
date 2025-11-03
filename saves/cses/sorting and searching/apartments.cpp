#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> people, appartments;

int main() {
    ll amountp, amounta, dif, temp;
    int p, a, total = 0;
    cin >> amountp >> amounta >> dif;
    for(int i = 0; i < amountp; i++)
    {
        cin >> temp;
        people.push_back(temp);
    }
    for(int i = 0; i < amounta; i++)
    {
        cin >> temp;
        appartments.push_back(temp);
    }
    sort(people.begin(), people.end());
    sort(appartments.begin(), appartments.end());
    p = 0, a = 0;
    while(p < amountp && a < amounta)
    {
        if(abs(people[p] - appartments[a]) <= dif) 
        {
            a++;
            p++;
            total++;
        }
        else if(people[p] > appartments[a]) a++;
        else p++;
    }
    cout << total;
}