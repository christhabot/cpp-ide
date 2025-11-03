#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

unordered_set<ll> st;

int main()
{
    ll amount, temp;
    scanf("%lld", &amount);
    for(int i = 0; i < amount; i++)
    {
        scanf("%lld", &temp);
        st.insert(temp);
    }
    printf("%d", st.size());
}