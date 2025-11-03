#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int gett(char thing)
{
    if(thing == '*') return 1;
    return 0;
}

int main() {
    ll amount, temp2, amountq, x1, y1, x2, y2, result;
    char temp;
    cin >> amount >> amountq;
    int prefix[1001][1001] = {0};
    scanf(" %c",&temp);
    temp2 = gett(temp);
    prefix[1][1] = temp2;
    for(int i = 2; i <= amount; i++) 
    {
        scanf(" %c",&temp);
        temp2 = gett(temp);
        prefix[1][i] = prefix[1][i-1] + temp2;
    }
    for(int i = 2; i <= amount; i++)
    {
        scanf(" %c",&temp);
        temp2 = gett(temp);
        prefix[i][1] = prefix[i-1][1] + temp2;
        for(int j = 2; j <= amount; j++)
        {
            scanf(" %c",&temp);
            temp2 = gett(temp);
            prefix[i][j] = prefix[i][j-1] + prefix[i-1][j] - prefix[i-1][j-1] + temp2;
        }
    }

    for(int i = 0; i < amountq; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        result = 0;
        result += prefix[x2][y2];
        result -= prefix[x1-1][y2];
        result -= prefix[x2][y1-1];
        result += prefix[x1-1][y1-1];
        cout << result << "\n";
    }
    return 0;
}