#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

stack<bool> st;
vector<int> starting;

int main() 
{
    int amount, total = 0, am;
    char temp;
    bool cur, dont;
    int last = 0;
    scanf("%d", &amount);
    for(int i = 0; i < amount; i++)
    {
        scanf(" %c", &temp);
        cur = temp == '(';
        if(!cur)
        {
            if(!st.empty()) st.pop();
            am = 1;
            for(int j = 0; j < starting.size(); j++)
            {
                cout << i << " " << starting[j] << "\n";
                total++;
            }
            do
            {
                if(st.empty())
                {
                    am = 0;
                    starting = {};
                    continue;
                }
                if(st.top())
                {
                    starting.pop_back();
                    am--;
                }
                else
                {
                    am++;
                }
                st.pop();
            } while(am > 0);
        }
        else
        {
            starting.push_back(i);
        }
    }
    printf("%d", total);
}