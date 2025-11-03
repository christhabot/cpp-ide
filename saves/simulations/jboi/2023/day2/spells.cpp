#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, m;

vector<int> cnt;
vector<int> siz;

int findMaxSafety() {
    vector<int> scrolls;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            scrolls.push_back(i);
        }
    }
    
    int maxSafety = 1;
    
    do {
        vector<set<int>> spots(m);
        
        int idx = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < siz[i]; j++) {
                spots[i].insert(scrolls[idx++]);
            }
        }
        
        vector<pair<int, int>> spotPairs; 
        for (int i = 0; i < m; i++) {
            spotPairs.push_back({siz[i], i});
        }
        sort(spotPairs.begin(), spotPairs.end());
        
        int chainLen = 1;
        int currentLen = 1;
        
        for (int i = 1; i < m; i++) {
            int prev = spotPairs[i-1].second;
            int curr = spotPairs[i].second;
            
            bool isSubset = true;
            for (int spell : spots[prev]) {
                if (spots[curr].find(spell) == spots[curr].end()) {
                    isSubset = false;
                    break;
                }
            }
            
            if (isSubset) {
                currentLen++;
            } else {
                currentLen = 1;
            }
            
            chainLen = max(chainLen, currentLen);
        }
        
        maxSafety = max(maxSafety, chainLen);
        
    } while (next_permutation(scrolls.begin(), scrolls.end()));
    
    return maxSafety;
}

int main() 
{
    scanf("%d %d", &n, &m);
    cnt.resize(n);
    siz.resize(m);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &cnt[i]);
    }
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &siz[i]);
    }
    printf("%d", findMaxSafety());
}