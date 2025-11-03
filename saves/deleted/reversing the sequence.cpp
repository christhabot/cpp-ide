#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> vec;

int main() 
{
    int amount;
    scanf("%d", &amount);
    vec.resize(amount);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &vec[i]);
    }
    for(int i = amount-1; i >= 0; i--)
    {
        printf("%d ", vec[i]);
    }
}