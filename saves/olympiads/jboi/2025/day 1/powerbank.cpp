#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll amount, switches;
float charge;

priority_queue<float, vector<float>, greater<float>> vec;
priority_queue<float, vector<float>, greater<float>> vect;
vector<float> vec2;

bool possible(float i) // amount of charge difference
{
    // cout << "\n\n\n";
    // cout << i << ":\n";
    ll cur = 0;
    float tp;
    do
    {
        cur++;
        tp = vect.top();
        // cout << tp << " ";
        vect.pop();
        if(tp >= charge)
        {
            return true;
        }
        if(cur > switches+1)
        {
            return false;
        }
        if(vect.top() + i < charge)
        {
            vect.push(vect.top() + i);
            // cout << "pushed " << vect.top() + i << "\n";
        }
        else
        {
            vect.push(charge);
            // cout << "pushed charge " << charge << "\n";
        }
    } while (true);
    cout << "AAAAAAAAAAAAAAAAAAAAAAAA";
}

int main()
{
    float temp;
    scanf("%lld %f %lld", &amount, &charge, &switches);
    for(int i = 0; i < amount; i++)
    {
        scanf("%f", &temp);
        vec.push(temp);
        vec2.push_back(temp);
    }
    sort(vec2.begin(), vec2.end());
    float mindif = abs(vec2[amount-1] - vec2[0]);
    float l = mindif, r = charge, mid;
    // cout << l << " " << r << "\n";
    while(r > l + 0.0000005)
    {
        mid = (l + r) / 2;
        vect = vec;
        if(possible(mid))
        {
            r = mid;
        }
        else
        {
            l = mid;

        }
        // cout << "R: " << r << "\n";
    }
    printf("%f", l);
}
