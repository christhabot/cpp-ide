#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

static const ll big = (ll)1e18;

// 0 cell 1 stamp
struct State {
    ll type;
    ll i, j;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll R, C, N;
    ll Sr, Sc, Gr, Gc;
    cin >> R >> C >> N >> Sr >> Sc >> Gr >> Gc;
    Sr--;
    Sc--;
    Gr--;
    Gc--;

    vector<string> G(R);
    for(ll i = 0; i < R; i++){
        cin >> G[i];
    }

    ll SR = R - N + 1;
    ll SC = C - N + 1;

    vector<vector<ll>> dist_cell(R, vector<ll>(C, big));
    vector<vector<ll>> dist_stamp(SR, vector<ll>(SC, big));

    deque<State> dq;
    dist_cell[Sr][Sc] = 0;
    dq.push_front({0, Sr, Sc});

    auto push_stamp = [&](ll a, ll b, ll d){
        if(d < dist_stamp[a][b]){
            dist_stamp[a][b] = d;
            dq.push_back({1, a, b});  // <-------------------------------------------------------
        }
    };

    ll dr4[4] = {-1, 1, 0, 0}, dc4[4] = {0, 0, -1, 1};

    vector<vector<vector<pair<ll,ll>>>> covers(R, vector<vector<pair<ll,ll>>>(C)); // ----<

    // optimisation
    for (ll a = 0; a < SR; ++a) {
        for (ll b = 0; b < SC; ++b) {
            for (ll di = 0; di < N; ++di) {
                for (ll dj = 0; dj < N; ++dj) {
                    ll i = a + di, j = b + dj;
                    covers[i][j].emplace_back(a, b);
                }
            }
        }
    }


    while(!dq.empty()){
        auto [type, i, j] = dq.front();
        dq.pop_front();

        if(type == 0){
            ll d = dist_cell[i][j];
            if(i == Gr && j == Gc) break;

            // 0 cost walk
            for(ll k = 0; k < 4; ++k){
                ll ni = i + dr4[k], nj = j + dc4[k];
                if(ni<0||ni>=R||nj<0||nj>=C) continue;
                if(G[ni][nj]=='.' && d < dist_cell[ni][nj]){
                    dist_cell[ni][nj] = d;
                    dq.push_front({0, ni, nj});
                }
            }

            // stamp if covers i,j or any neighbours
            static const ll dr5[5] = {0, -1, +1, 0, 0 };
            static const ll dc5[5] = {0, 0, 0, -1, +1 };
            for(ll z = 0; z < 5; ++z){
                ll x = i + dr5[z];
                ll y = j + dc5[z];
                if(x<0||x>=R||y<0||y>=C) continue;
                for (auto [a, b] : covers[x][y]) {
                    push_stamp(a, b, d + 1);
                }
            }
        }
        else {
            ll d = dist_stamp[i][j];
            // spread
            for(ll di = 0; di < N; ++di){
                for(ll dj = 0; dj < N; ++dj){
                    ll ci = i + di, cj = j + dj;
                    if(ci >= R || cj >= C) continue;
                    if(d < dist_cell[ci][cj]){
                        dist_cell[ci][cj] = d;
                        dq.push_front({0, ci, cj});
                    }
                }
            }
        }
    }

    ll ans = dist_cell[Gr][Gc];
    if(ans >= big) cout << "-1\n";
    else cout << ans << "\n";
    return 0;
}
