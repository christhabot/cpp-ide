#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() 
{
    int number, steps = 0;
    string str;
    scanf("%d", &number);
    while(number > 0)
    {
        str = to_string(number);
        number -= *max_element(str.begin(), str.end()) - '0';
        steps++;
    }
    printf("%d", steps);
}