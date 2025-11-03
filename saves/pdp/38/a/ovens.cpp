#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<bool> stat;
vector<int> nxt;
priority_queue<int> pq;

int main() 
{
    int amount, pqt = -1, cur, total = 0, add = 0, temp;
    bool fin;
    scanf("%d", &amount);
    stat.resize(amount);
    nxt.resize(amount);
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &temp);
        stat[i] = temp == 1;
    }
    for(int i = 0; i < amount; i++)
    {
        scanf("%d", &nxt[i]);
    }
    for(int i = 0; i < amount; i++)
    {
        while(!pq.empty() && pqt == i)
        {
            add--;
            pq.pop();
            pqt = pq.top();
        }
        cur = (int)stat[i] + add;
        fin = cur % 2 == 1;
        if(fin)
        {
            cout << i << " " << add << "\n";
            total++;
            pq.push(i+nxt[i]+1);
            add++;
            pqt = pq.top();
        }
    }
    printf("%d", total);
}