#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> X;

ll calc_brute(const vector<ll>& balls, ll S, ll G){
    int N = balls.size();
    vector<int> idx(N);
    iota(idx.begin(), idx.end(), 0);
    ll best = LLONG_MAX;
    do {
        ll time = 0, pos = S, carry = 0;
        for (int j = 0; j < N; j++) {
            ll target = balls[idx[j]];
            time += llabs(pos - target) * (carry + 1);
            time += 1;
            carry++;
            pos = target;
        }
        time += llabs(pos - G) * (carry + 1);
        best = min(best, time);
    } while (next_permutation(idx.begin(), idx.end()));
    return best;
}

ll calc_dp(const vector<ll>& balls, ll S, ll G){
    int N = balls.size();
    int M = 1 << N;
    static ll dp[1<<14][14];
    for (int m = 0; m < M; m++)
        for (int i = 0; i < N; i++)
            dp[m][i] = LLONG_MAX;
    for (int i = 0; i < N; i++) {
        ll d = llabs(S - balls[i]);
        dp[1<<i][i] = d * 1 + 1;
    }
    for (int m = 1; m < M; m++) {
        int c = __builtin_popcount(m);
        for (int i = 0; i < N; i++) if (m & (1<<i)) {
            ll v = dp[m][i];
            if (v == LLONG_MAX) continue;
            for (int j = 0; j < N; j++) if (!(m & (1<<j))) {
                ll d = llabs(balls[i] - balls[j]);
                ll nv = v + d * (c + 1) + 1;
                int m2 = m | (1<<j);
                dp[m2][j] = min(dp[m2][j], nv);
            }
        }
    }
    ll best = LLONG_MAX;
    int full = M - 1;
    for (int i = 0; i < N; i++) {
        ll v = dp[full][i];
        if (v == LLONG_MAX) continue;
        v += llabs(balls[i] - G) * (N + 1);
        best = min(best, v);
    }
    return best;
}

int main(){
    ll N, L;
    scanf("%lld %lld", &N, &L);
    X.resize(N);
    for (int i = 0; i < N; i++) scanf("%lld", &X[i]);
    sort(X.begin(), X.end());
    int Q;
    scanf("%d", &Q);
    vector<ll> S(Q), G(Q), T(Q);
    for (int i = 0; i < Q; i++) scanf("%lld %lld %lld", &S[i], &G[i], &T[i]);

    if (N <= 7 && Q <= 10) 
    {
        for (int i = 0; i < Q; i++) 
        {
            ll best = calc_brute(X, S[i], G[i]);
            printf("%s\n", best <= T[i] ? "Yes" : "No");
        }
    } else 
    {
        for (int i = 0; i < Q; i++) 
        {
            ll best = calc_dp(X, S[i], G[i]);
            printf("%s\n", best <= T[i] ? "Yes" : "No");
        }
    }
    return 0;
}
