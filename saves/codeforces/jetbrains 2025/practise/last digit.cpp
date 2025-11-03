#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> vec = {2,4,8,6};

int main() 
{
    int i;
    scanf("%d", &i);
    if(i < 10)
    {
        printf("%d", (int)pow(2, i) % 10);
    }
    else
    {
        printf("%d", vec[(i-1)%4]);
    }
}