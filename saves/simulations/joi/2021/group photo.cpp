#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll merge_sort_count(vector<ll>& arr, vector<ll>& temp, ll left, ll right) {
    if (right - left <= 1) return 0;
    ll mid = (left + right) / 2;
    ll inv = merge_sort_count(arr, temp, left, mid) + merge_sort_count(arr, temp, mid, right);

    ll i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else {
            temp[k++] = arr[j++];
            inv += mid - i;
        }
    }
    while (i < mid) temp[k++] = arr[i++];
    while (j < right) temp[k++] = arr[j++];

    for (ll idx = left; idx < right; ++idx) arr[idx] = temp[idx];
    return inv;
}

int main() {
    ll amount;
    scanf("%lld", &amount);
    vector<ll> people(amount), positions(amount), postemp(amount);
    for (ll i = 0; i < amount; i++) {
        scanf("%lld", &people[i]);
        positions[i] = i;
    }

    vector<ll> temp(amount);
    ll optimal = LLONG_MAX;
    if(amount > 20)
    {
        optimal = 1;
    }
    else
    {
        do {
            bool no = false;
            for (int i = 1; i < amount; i++) {
                if (people[positions[i-1]] - people[positions[i]] >= 2) {
                    no = true;
                    break;
                }
            }
            if (no) continue;

            for (int i = 0; i < amount; i++) {
                postemp[positions[i]] = i;
            }
            ll current = merge_sort_count(postemp, temp, 0, amount);
            if (current < optimal) optimal = current;

        } while (next_permutation(positions.begin(), positions.end()));
    }
    printf("%lld\n", optimal);
}
