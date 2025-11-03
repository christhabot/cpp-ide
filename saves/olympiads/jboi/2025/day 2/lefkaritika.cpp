#include <bits/stdc++.h>

using namespace std;

vector<pair<pair<int,int>, pair<int,int>>> vec;
vector<pair<pair<int, pair<int,int>>,string>> vec2;
vector<pair<pair<int,int>,pair<int,int>>> fin;

void solve(int amount, int amountt)
{
    fin.clear();
    for(int i = 0; i < amount-1; i++)
    {
        for(int j = 0; j < amountt-1; j++)
        {
            fin.push_back({{i, j},{i+1, j}});
            fin.push_back({{i, j},{i, j+1}});
            fin.push_back({{i, j},{i+1, j+1}});
        }
    }
    for(int i = 0; i < amount-1; i++)
    {
        fin.push_back({{i, amountt-1},{i+1, amountt-1}});
    }
    for(int i = 0; i < amountt-1; i++)
    {
        fin.push_back({{amount-1, i},{amount-1, i+1}});
    }
    printf("%d\n", fin.size());
    for(int i = 0; i < fin.size(); i++)
    {
        printf("%d %d %d %d\n", fin[i].first.first, fin[i].first.second, fin[i].second.first, fin[i].second.second);
    }
}

int main()
{
    int amount, amountt;
    string in, out;
    for(int i = 0; i <= 20; i++)
    {
        if(i < 10)
        {
            in = "0" + to_string(i) + ".txt";
        }
        else
        {
            in = to_string(i) + ".txt";
        }
        out = "output_" + in;
        freopen(in.c_str(), "r", stdin);
        freopen(out.c_str(), "w", stdout);
        scanf("%d %d", &amount, &amountt);

        solve(amount, amountt);
    }
}