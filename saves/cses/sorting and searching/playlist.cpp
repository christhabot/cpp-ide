#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> songs;

unordered_set<int> used;

int main() 
{
    int amount;
    int start, end, i;
    int best = 1;
    scanf("%d", &amount);
    used.reserve(amount);
    songs.assign(amount, -1);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &songs[i]);
    }
    start = 0;
    end = 0;
    used.insert(songs[0]);
    while(end < amount-1)
    {
        end++;
        if(used.count(songs[end]))
        {
            i = start;
            while(i < amount && songs[i] != songs[end])
            {
                used.erase(songs[i]);
                i++;
            }
            used.erase(songs[i]);
            start = i + 1;
        }
        used.insert(songs[end]);
        best = max(best, end-start+1);
    }
    printf("%d", best);
}