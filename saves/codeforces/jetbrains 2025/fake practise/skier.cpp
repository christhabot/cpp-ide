#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct pair_hash {
    size_t operator()(const pair<ll,ll>& p) const noexcept {
        // boost-like mix
        uint64_t h1 = std::hash<ll>()(p.first);
        uint64_t h2 = std::hash<ll>()(p.second);
        h1 ^= h2 + 0x9e3779b97f4a7c15ULL + (h1<<6) + (h1>>2);
        return (size_t)h1;
    }
};

struct edge_hash {
    size_t operator()(const pair<pair<ll,ll>, pair<ll,ll>>& e) const noexcept {
        pair_hash ph;
        uint64_t h1 = ph(e.first);
        uint64_t h2 = ph(e.second);
        h1 ^= h2 + 0x9e3779b97f4a7c15ULL + (h1<<6) + (h1>>2);
        return (size_t)h1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int amountq;
    if (!(cin >> amountq)) return 0;
    while (amountq--) {
        string s;
        cin >> s;
        ll x = 0, y = 0;
        unordered_set<pair<pair<ll,ll>, pair<ll,ll>>, edge_hash> seen;
        ll time = 0;
        for (char c : s) {
            ll nx = x, ny = y;
            if (c == 'N') nx--;
            else if (c == 'S') nx++;
            else if (c == 'E') ny++;
            else if (c == 'W') ny--;
            pair<ll,ll> a = {x,y}, b = {nx,ny};
            pair<pair<ll,ll>, pair<ll,ll>> edge = (a < b) ? make_pair(a,b) : make_pair(b,a);
            if (seen.find(edge) != seen.end()) time += 1;
            else {
                time += 5;
                seen.insert(edge);
            }
            x = nx; y = ny;
        }
        printf("%lld\n", time);
    }
    return 0;
}
