#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    long long amount, temp, total = 0, small = 0, answer = INT_MAX * -1;
    cin >> amount;
    for(int i = 0; i < amount; i++) 
    {
        cin >> temp;
        total += temp;
        //cout << total << "\n";
        answer = max(answer, total - small);
        small = min(small,total);
    }
    cout << answer;
    return 0;
}