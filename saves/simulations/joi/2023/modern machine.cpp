#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<char> tiles;
vector<char> tilest;
vector<ll> buttons;

int main() {
    ll amount, amountB, amountQ;
    char temp;
    ll temp2, start, end, ball, button, p, reds, redso = 0;
    scanf("%lld %lld", &amount, &amountB);
    tiles.reserve(amount);
    for(int i = 0; i < amount; i++)
    {
        scanf(" %c", &temp);
        tiles.push_back(temp);
        if(temp == 'R') redso++;
    }
    buttons.reserve(amountB);
    for(int i = 0; i < amountB; i++)
    {
        scanf("%lld", &temp2);
        buttons.push_back(temp2);
    }
    scanf("%lld", &amountQ);
    for(int q = 0; q < amountQ; q++)
    {
        scanf("%lld %lld", &start, &end);
        tilest = tiles;
        reds = redso;
        for(int i = start; i <= end; i++)
        {
            button = buttons[i-1] - 1;
            ball = button;
            if(tilest[button] == 'B') reds++;
            tilest[button] = 'R';
            while(true)
            {
                p = ball;
                if(tilest[p] == 'B')
                {
                    reds++;
                    tilest[p] = 'R';
                    if(p == 0) 
                    {
                        break;
                    }
                    else ball--;
                }
                else
                {
                    reds--;
                    tilest[p] = 'B';
                    if(p == amount-1) 
                    {
                        break;
                    }
                    else ball++;
                }
            }
        }
        printf("%lld\n", reds);
    }
}