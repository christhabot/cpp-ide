#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int res, res2;
    printf("? 2 15000 1\n");
    fflush(stdout);
    scanf("%d", &res);
    printf("? 2 14999 1\n");
    fflush(stdout);
    scanf("%d", &res2);
    if(res == res2)
    {
        printf("! %d\n", res);
    }
    else
    {
        if(res == 1)
        {
            printf("! 15000\n");
        }
        else if(res == 14999)
        {
            printf("! 14999\n");
        }
        else if(res == 2 && res2 == 4)
        {
            printf("! 30000\n");
        }
        else
        {
            printf("! %d\n", res + 15000 - 1);
        }
    }
}
