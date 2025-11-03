#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int solve(vector<int> a, vector<int> b) {
    int n = a.size();
    if(n == 0) return 0;
    
    int ans = 0;
    for(int i = 0; i < n; i++) {
        set<int> reachA, reachB;
        for(int j = i; j < n; j++) {
            reachA.insert(a[j] - (j - i));
        }
        for(int k = i; k < n; k++) {
            reachB.insert(b[k] - (k - i));
        }
        
        bool found = false;
        for(int val : reachA) {
            if(reachB.count(val)) {
                found = true;
                break;
            }
        }
        if(found) ans++;
    }
    
    return ans;
}

int main() 
{
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    
    int ans = solve(a, b);
    
    for(int skip = 0; skip < n; skip++) {
        vector<int> na, nb;
        for(int i = 0; i < n; i++) {
            if(i != skip) {
                na.push_back(a[i]);
                nb.push_back(b[i]);
            }
        }
        ans = max(ans, solve(na, nb));
    }
    
    cout << ans << endl;
    
    return 0;
}