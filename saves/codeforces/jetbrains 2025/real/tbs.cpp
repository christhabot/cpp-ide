#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> arr, new_arr;

vector<ll> prefix_op(const vector<ll> &arr)
{
    ll n = arr.size();
    new_arr.assign(n-1, 0);
    ll xor_sum = 0;
    for(ll i = 0; i < n-1; i++)
    {
        xor_sum ^= arr[i];
        new_arr[i] = xor_sum ^ arr[i+1];
    }
    return new_arr;
}

vector<ll> suffix_op(const vector<ll> &arr)
{
    ll n = arr.size();
    new_arr.assign(n-1, 0);
    ll xor_sum = 0;
    for(ll i = 0; i < n-1; i++)
    {
        xor_sum ^= arr[n-1-i];
        new_arr[n-2-i] = xor_sum ^ arr[n-2-i];
    }
    return new_arr;
}

string dfs(const vector<ll> &arr, string path)
{
    if(arr.size() == 1)
    {
        if(arr[0] == 1)
            return path;
        else
            return "";
    }

    string res = dfs(prefix_op(arr), path + "1");
    if(!res.empty())
        return res;

    res = dfs(suffix_op(arr), path + "2");
    if(!res.empty())
        return res;

    return "";
}

int main()
{
    ll t;
    scanf("%lld", &t);

    for(ll test = 0; test < t; test++)
    {
        ll n;
        scanf("%lld", &n);
        arr.assign(n, 0);
        char buf[n+1];
        scanf("%s", buf);
        for(ll i = 0; i < n; i++)
            arr[i] = buf[i] - '0';

        string res = dfs(arr, "");
        if(res.empty())
        {
            printf("0\n");
        }
        else
        {
            printf("1\n%s\n", res.c_str());
        }
    }

    return 0;
}
