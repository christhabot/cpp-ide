#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll stations, limit, lines, amountQ;
    scanf("%lld %lld", &stations, &limit);
    scanf("%lld", &lines);
    int N = stations;
    vector<vector<ll>> addF(N+2), remF(N+2), addB(N+2), remB(N+2);
    ll temp1, temp2;
    for (int i = 0; i < lines; i++) {
    scanf("%lld %lld", &temp1, &temp2);
    if (temp1 < temp2) {
            // forward
            ll a = temp1, b = temp2;
            ll l = a;
            ll r = min(a + limit - 1, b - 1);
            if (l <= r) {
                addF[l].push_back(b);
                remF[r + 1].push_back(b);
            }
        } else {
            // backward
            ll a = temp1, b = temp2;
            ll ar = N + 1 - a;
            ll br = N + 1 - b;
            ll l  = ar;
            ll r  = min(ar + limit - 1, br - 1);
            if (l <= r) {
                addB[l].push_back(br);
                remB[r + 1].push_back(br);
            }
        }
    }
    vector<int> maxF(N+2), maxB(N+2);
    multiset<ll> sf, sb;
    for(int i = 1; i <= N; i++){
        for(ll x : addF[i]) sf.insert(x);
        for(ll x : remF[i]){
            auto it = sf.find(x);
            if(it != sf.end()) sf.erase(it);
        }
        maxF[i] = sf.empty() ? i : *sf.rbegin();
        for(ll x : addB[i]) sb.insert(x);
        for(ll x : remB[i]){
            auto it = sb.find(x);
            if(it != sb.end()) sb.erase(it);
        }
        maxB[i] = sb.empty() ? i : *sb.rbegin();
    }
    int LOG = 0;
    while((1<<LOG) <= N) LOG++;
    vector<vector<int>> jumpF(LOG, vector<int>(N+2)), jumpB(LOG, vector<int>(N+2));
    for(int i = 1; i <= N; i++){
        jumpF[0][i] = maxF[i];
        jumpB[0][i] = maxB[i];
    }
    for(int k = 1; k < LOG; k++){
        for(int i = 1; i <= N; i++){
            jumpF[k][i] = jumpF[k-1][ jumpF[k-1][i] ];
            jumpB[k][i] = jumpB[k-1][ jumpB[k-1][i] ];
        }
    }
    scanf("%lld", &amountQ);
    ll start, end;
    while(amountQ--){
        scanf("%lld %lld", &start, &end);
        if(start == end){
            cout << 0 << "\n";
        } else if(start < end){
            ll pos = start;
            int ans = 0;
            for(int k = LOG-1; k >= 0; k--){
                if(jumpF[k][pos] < end){
                    pos = jumpF[k][pos];
                    ans += (1<<k);
                }
            }
            if(jumpF[0][pos] < end) cout << -1 << "\n";
            else cout << ans+1 << "\n";
        } else {
            ll sr = N + 1 - start;
            ll er = N + 1 - end;
            ll pos = sr;
            int ans = 0;
            for(int k = LOG-1; k >= 0; k--){
                if(jumpB[k][pos] < er){
                    pos = jumpB[k][pos];
                    ans += (1<<k);
                }
            }
            if(jumpB[0][pos] < er) cout << -1 << "\n";
            else cout << ans+1 << "\n";
        }
    }
    return 0;
}
